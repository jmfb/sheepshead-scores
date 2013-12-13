#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
			<< "};" << std::endl;
	}
	
	void WriteSource() const
	{
		std::ofstream out(name + "View.cpp");
		out << "#include \"" << name << "View.h\"" << std::endl;
	}

private:
	std::string name;
	std::string layout;
	std::string model;
	std::vector<std::string> sections;
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

void CompileView(const std::string& fileName)
{
	View view;
	view.SetName(GetViewName(fileName));
	
	std::ifstream in(fileName);
	std::string line;
	while (std::getline(in, line))
	{
		std::string directiveValue;
		if (ParseDirective(line, "layout", directiveValue))
		{
			view.SetLayout(directiveValue);
		}
		else if (ParseDirective(line, "model", directiveValue))
		{
			view.SetModel(directiveValue);
		}
		else
		{
			//TODO:
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

