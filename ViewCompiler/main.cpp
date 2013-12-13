#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class View
{
public:
	void SetName(const std::string& value)
	{
		name = value;
	}
	
	void SetLayout(const std::string& value)
	{
		layout = value;
	}
	
	void SetModel(const std::string& value)
	{
		model = value;
	}
	
	void AddSection(const std::string& value)
	{
		sections.push_back(value);
	}
	
	void AddBodyLine(const std::string& line)
	{
		auto openBraceCount = 0;
		ParseLine(line, body, openBraceCount);
	}
	
	void AddSectionLine(const std::string& section, const std::string& line, int& openBraceCount)
	{
		ParseLine(line, sectionBodies[section], openBraceCount);
	}
	
	void WriteHeader() const
	{
		std::ofstream out(name + "View.h");
		out << "#pragma once" << std::endl;
		auto baseView = layout.empty() ? "BaseView" : layout + "View";
		out << "#include \"" << baseView << ".h\"" << std::endl;
		if (!model.empty())
			out << "#include \"" << model << ".h\"" << std::endl;
		out << std::endl
			<< "class " << name << "View : public " << baseView << std::endl
			<< "{" << std::endl
			<< "public:" << std::endl
			<< "\t" << name << "View() = default;" << std::endl
			<< "\t" << name << "View(const " << name << "View& rhs) = delete;" << std::endl
			<< "\t~" << name << "View() = default;" << std::endl
			<< std::endl
			<< "\t" << name << "View& operator=(const " << name << "View& rhs) = delete;" << std::endl
			<< std::endl;

		out << "\tvirtual void RenderBody_" << name << "();" << std::endl;
		for (auto section : sections)
			out << "\tvirtual void RenderSection_" << name << "_" << section << "();" << std::endl;
		if (layout.empty())
			out << "\tvirtual void RenderBody();" << std::endl;
		else
			out << "\tvirtual void RenderBody_" << layout << "();" << std::endl;
		for (auto section : sectionBodies)
			out << "\tvirtual void RenderSection_" << layout << "_" << section.first << "();" << std::endl;
		out << std::endl;
		
		if (!model.empty())
		{
			out << "\tvoid SetModel(const " << model << "& value);" << std::endl
				<< std::endl
				<< "private:" << std::endl
				<< "\t" << model << " model;" << std::endl;
		}	
		
		out << "};" << std::endl;
	}
	
	void WriteSource() const
	{
		std::ofstream out(name + "View.cpp");
		out << "#include \"" << name << "View.h\"" << std::endl
			<< std::endl;
			
		out << "void " << name << "View::RenderBody_" << name << "()" << std::endl
			<< "{" << std::endl
			<< "}" << std::endl
			<< std::endl;
			
		for (auto section : sections)
			out << "void " << name << "View::RenderSection_" << name << "_" << section << "()" << std::endl
				<< "{" << std::endl
				<< "}" << std::endl
				<< std::endl;
				
		if (layout.empty())
			out << "void " << name << "View::RenderBody()" << std::endl;
		else
			out << "void " << name << "View::RenderBody_" << layout << "()" << std::endl;
		out << "{" << std::endl;
		WriteSection(body, out);
		out << "}" << std::endl
			<< std::endl;
			
		for (auto section : sectionBodies)
		{
			out << "void " << name << "View::RenderSection_" << layout << "_" << section.first << "()" << std::endl
				<< "{" << std::endl;
			WriteSection(section.second, out);
			out << "}" << std::endl
				<< std::endl;
		}
	}
	
private:
	static void ParseLine(const std::string& line, std::vector<std::string>& section, int& openBraceCount)
	{
		std::ostringstream buffer;
		enum { html, directive, value } state = html;
		for (auto ch : line)
		{
			switch (state)
			{
			case html:
				//TODO:
				break;
				
			case directive:
				//TODO:
				break;
				
			case value:
				//TODO:
				break;
			}
		}
		//TODO: deal with leftover buffer
		section.push_back("Write(\"\\n\");");
	}
	
	void WriteSection(const std::vector<std::string>& section, std::ostream& out) const
	{
		for (auto line : section)
			out << "\t" << line << std::endl;
	}

private:
	std::string name;
	std::string layout;
	std::string model;
	std::vector<std::string> sections;
	std::vector<std::string> body;
	std::map<std::string, std::vector<std::string>> sectionBodies;
};

std::string GetViewName(const std::string& fileName)
{
	auto index = fileName.find('.');
	if (index == std::string::npos)
		return fileName;
	return fileName.substr(0, index);
}

bool ParseDirective(const std::string& line, const std::string& directive, std::string& value)
{
	if (line.find("@" + directive + " ") != 0)
		return false;
	auto start = 2 + directive.size();
	auto index = line.find(";");
	value = index == std::string::npos ? line.substr(start) : line.substr(start, index - start);
	return true;
}

bool ParseSection(const std::string& line, std::string& name, std::size_t& sectionStart)
{
	if (line.find("@section ") != 0)
		return false;
	auto braceIndex = line.find("{");
	if (braceIndex == std::string::npos)
		return false;
	name = line.substr(9, braceIndex - 10);
	sectionStart = braceIndex + 1;
	return true;
}

void CompileView(const std::string& fileName)
{
	View view;
	view.SetName(GetViewName(fileName));
	
	std::ifstream in(fileName);
	std::string line;
	std::string currentSection;
	auto openBraceCount = 0;
	while (std::getline(in, line))
	{
		std::size_t sectionStart = 0;
		std::string directiveValue;
		if (ParseDirective(line, "layout", directiveValue))
		{
			view.SetLayout(directiveValue);
			continue;
		}
		else if (ParseDirective(line, "model", directiveValue))
		{
			view.SetModel(directiveValue);
			continue;
		}
		else if (ParseSection(line, directiveValue, sectionStart))
		{
			currentSection = directiveValue;
			openBraceCount = 1;
		}
		
		if (currentSection.empty())
		{
			view.AddBodyLine(line);
		}
		else
		{
			view.AddSectionLine(currentSection, line.substr(sectionStart), openBraceCount);
			sectionStart = 0;
			if (openBraceCount == 0)
				currentSection.clear();
		}
	}
	
	view.WriteHeader();
	view.WriteSource();
}

int main(int argc, char** argv)
{
	std::string fileName;
	while (std::getline(std::cin, fileName))
		CompileView(fileName);
	return 0;
}

