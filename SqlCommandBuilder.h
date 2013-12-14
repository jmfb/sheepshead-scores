#pragma once
#include "StringUtility.h"
#include <string>
#include <pqxx/pqxx>

template <int TIndex, typename... TArgs>
class SqlCommandBuilder
{
};

template <int TIndex, typename T, typename... TArgs>
class SqlCommandBuilder<TIndex, T, TArgs...>
{
public:
	static std::string Build(pqxx::work& transaction, const std::string& sql, T arg, TArgs... args)
	{
		return SqlCommandBuilder<TIndex + 1, TArgs...>::Build(
			transaction,
			String::Replace(sql, "{" + std::to_string(TIndex) + "}", transaction.quote(arg)),
			args...);	
	}
};

template <int TIndex>
class SqlCommandBuilder<TIndex>
{
public:
	static std::string Build(pqxx::work& transaction, const std::string& sql)
	{
		return sql;
	}
};

