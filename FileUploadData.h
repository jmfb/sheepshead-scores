#pragma once
#include <string>

class FileUploadData
{
public:
	FileUploadData();
	FileUploadData(const FileUploadData& rhs) = default;
	~FileUploadData() = default;
	
	FileUploadData& operator=(const FileUploadData& rhs) = default;
	
	const std::string& GetContentDisposition() const;
	const std::string& GetContentType() const;
	const std::string& GetContent() const;

private:
	std::string contentDisposition;
	std::string contentType;
	std::string content;
};

