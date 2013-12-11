#pragma once
#include <string>
#include <map>
#include <vector>

class FormData
{
public:
	typedef std::vector<std::string> ValueType;
	typedef std::map<std::string, ValueType> MapType;
	typedef MapType::const_iterator IteratorType;

	FormData(const std::string& urlEncodedFormData);
	FormData(const FormData& rhs) = default;
	~FormData() = default;
	
	FormData& operator=(const FormData& rhs) = default;
	
	const ValueType& operator[](const std::string& key) const;
	const std::string& operator()(const std::string& key) const;
	
	IteratorType begin() const;
	IteratorType end() const;
	
private:
	MapType values;
};

