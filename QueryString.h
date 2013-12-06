#pragma once
#include <string>
#include <map>
#include <vector>

class QueryString
{
public:
	typedef std::vector<std::string> ValueType;
	typedef std::map<std::string, ValueType> MapType;
	typedef MapType::const_iterator IteratorType;

	QueryString();
	QueryString(const QueryString& rhs) = default;
	~QueryString() = default;
	
	QueryString& operator=(const QueryString& rhs) = default;
	
	const ValueType& operator[](const std::string& key) const;
	
	IteratorType begin() const;
	IteratorType end() const;
	
private:
	MapType values;
};

