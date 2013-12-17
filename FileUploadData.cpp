#include "FileUploadData.h"
#include <vector>
#include <cstdlib>
#include <sstream>

int GetContentLength2()
{
	auto value = std::getenv("CONTENT_LENGTH");
	return value == nullptr ? 0 : std::atoi(value);
}

std::string GetFileUploadBoundary()
{
	auto value = std::getenv("CONTENT_TYPE");
	if (value == nullptr)
		return "";
	std::string contentType = value;
	const std::string multipart = "multipart/form-data; boundary=";
	if (contentType.find(multipart) != 0)
		return "";
	return contentType.substr(multipart.size());
}

FileUploadData::FileUploadData()
{
	auto contentLength = GetContentLength2();
	auto boundary = GetFileUploadBoundary();
	if (contentLength < 1 || boundary.empty())
		return;

	std::vector<char> buffer(contentLength);
	std::fread(buffer.data(), sizeof(char), contentLength, stdin);
	std::istringstream in(buffer.data());
	std::string line;
	auto foundStart = false;
	auto foundContentDisposition = false;
	auto foundContentType = false;
	auto foundFirstBlankLine = false;
	while (std::getline(in, line))
	{
		if (!line.empty() && line.back() == '\r')
			line.erase(line.begin() + line.size() - 1);
		if (!foundStart)
		{
			if (line == "--" + boundary)
				foundStart = true;
		}
		else
		{
			if (line == "--" + boundary + "--")
				break;
			if (foundFirstBlankLine)
				content += line + "\n";
			else
			{
				const std::string contentDispositionPrefix = "Content-Disposition: ";
				const std::string contentTypePrefix = "Content-Type: ";
				if (!foundContentDisposition && line.find(contentDispositionPrefix) == 0)
				{
					contentDisposition = line.substr(contentDispositionPrefix.size());
					foundContentDisposition = true;
				}
				else if (!foundContentType && line.find(contentTypePrefix) == 0)
				{
					contentType = line.substr(contentType.size());
					foundContentType = true;
				}
				else if (!foundFirstBlankLine && line.empty())
				{
					foundFirstBlankLine = true;
				}
			}
		}
	}
}

const std::string& FileUploadData::GetContentDisposition() const
{
	return contentDisposition;
}

const std::string& FileUploadData::GetContentType() const
{
	return contentType;
}

const std::string& FileUploadData::GetContent() const
{
	return content;
}

