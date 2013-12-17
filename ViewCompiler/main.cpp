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
		auto openBraceCount = 2;
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
			<< "#include \"HtmlUtility.h\"" << std::endl
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
		
		if (!model.empty())
		{
			out << "void " << name << "View::SetModel(const " << model << "& value)" << std::endl
				<< "{" << std::endl
				<< "\tmodel = value;" << std::endl
				<< "}" << std::endl
				<< std::endl;
		}
	}
	
private:
	std::string Trim(const std::string& value)
	{
		auto first = value.find_first_not_of(" \t");
		if (first == std::string::npos)
			return {};
		auto last = value.find_last_not_of(" \t");
		if (last == std::string::npos)
			return value.substr(first);
		return value.substr(first, last - first + 1);
	}

	std::size_t NextEscapeToken(const std::string& line, std::size_t start)
	{
		auto openBraceCount = 0;
		for (auto index = start; index < line.size(); ++index)
		{
			auto ch = line[index];
			if (ch == '{')
				++openBraceCount;
			else if (ch == '@')
				return index;
			else if (ch == '}')
			{
				if (openBraceCount > 0)
					--openBraceCount;
				else
					return index;
			}
		}
		return std::string::npos;
	}

	void ParseLine(const std::string& line, std::vector<std::string>& section, int& openBraceCount)
	{
		// [@section Title {] title }
		// [@section Body {]
		//   <whatever>
		//   <div>{{blah}}</div>
		//   @for (auto x : y) {
		//     <div>@write x;</div>
		//   }
		// }
		std::size_t position = 0;
		while (position != std::string::npos && position < line.size())
		{
			auto next = NextEscapeToken(line, position);
			AddWrite(section, Trim(next == std::string::npos ?
				line.substr(position) :
				line.substr(position, next - position)));
			if (next == std::string::npos)
				break;
			if (line[next] == '}')
			{
				--openBraceCount;
				if (openBraceCount > 0)
					section.push_back("}");
				position = next + 1;
			}
			else //@
			{
				auto end = line.find_first_of(";{", next);
				if (end == std::string::npos)
				{
					position = std::string::npos;
					std::cout << "Missing ';' after '@' in " << name << " view." << std::endl;
					std::cout << line << std::endl;
				}
				else if (line[end] == ';')
				{
					AddDirective(section, line.substr(next, end - next));
					position = end + 1;
				}
				else
				{
					++openBraceCount;
					section.push_back(line.substr(next + 1, end - next));
					position = end + 1;
				}
			}
		}
		AddWrite(section, " ");
	}
	
	void AddWrite(std::vector<std::string>& section, const std::string& value)
	{
		if (value.empty())
			return;
		std::ostringstream out;
		out << "Write(\"";
		for (auto ch : value)
		{
			if (ch == '\\' || ch == '"')
				out << '\\';
			out << ch;
		}
		out << "\");";
		section.push_back(out.str());
	}
	
	void AddDirective(std::vector<std::string>& section, const std::string& directive)
	{
		if (directive == "@render-body")
		{
			section.push_back("RenderBody_" + name + "();");
			return;
		}
		auto space = directive.find(' ');
		if (space == std::string::npos)
		{
			std::cout << "Missing ' ' after '@' in " << name << "view." << std::endl;
			std::cout << directive << std::endl;
			return;
		}
		auto directiveName = directive.substr(0, space);
		if (directiveName == "@write")
		{
			section.push_back("Write(Html::EscapeHtml(" + directive.substr(space + 1) + "));");		
		}
		else if (directiveName == "@render")
		{
			auto sectionName = directive.substr(space + 1);
			section.push_back("RenderSection_" + name + "_" + sectionName + "();");
			sections.push_back(sectionName);
		}
		else
		{
			std::cout << "Invalid directive in " << name << " view: " << directive << std::endl;
		}
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
	auto lastSlash = fileName.rfind('/');
	auto index = fileName.find('.', lastSlash + 1);
	if (index == std::string::npos)
		return fileName.substr(lastSlash + 1);
	return fileName.substr(lastSlash + 1, index - lastSlash - 1);
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

