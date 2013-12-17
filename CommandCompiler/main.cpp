#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string FormatLine(const std::string& value)
{
	std::ostringstream out;
	for (auto ch : value)
	{
		if (ch == '\\' || ch == '"')
			out << '\\';
		out << ch;
	}
	return out.str();
}

int main()
{
	std::string fileName;
	std::ofstream out("Commands.h");
	out << "#pragma once" << std::endl
		<< "#include <string>" << std::endl
		<< std::endl
		<< "namespace Commands" << std::endl
		<< "{" << std::endl;
	while (std::getline(std::cin, fileName))
	{
		auto lastSlash = fileName.rfind('/');
		auto dot = fileName.find('.', lastSlash);
		auto name = dot == std::string::npos ?
			fileName.substr(lastSlash + 1) :
			fileName.substr(lastSlash + 1, dot - lastSlash - 1);
		out << "\tconst std::string " << name << " =";
		std::ifstream in(fileName);
		std::string line;
		while (std::getline(in, line))
			if (!line.empty())
				out << std::endl << "\t\t\"" << FormatLine(line) << "\\n\"";
		out << ";" << std::endl;
	}
	out << "}" << std::endl;
	return 0;
}

