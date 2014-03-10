#pragma once
#include "StringUtility.h"
#include "Nullable.h"
#include <string>
#include <pqxx/pqxx>
#include <stdexcept>
#include <iterator>
#include <algorithm>

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

template <int TIndex, typename T, typename... TArgs>
class SqlCommandBuilder<TIndex, Nullable<T>, TArgs...>
{
public:
	static std::string Build(
		pqxx::work& transaction,
		const std::string& sql,
		Nullable<T> arg,
		TArgs... args)
	{
		static const std::string nullString = "null";
		auto indexText = "{" + std::to_string(TIndex) + "}";
		auto valueText = arg == nullptr ? nullString : transaction.quote(arg.GetValue());
		return SqlCommandBuilder<TIndex + 1, TArgs...>::Build(
			transaction,
			String::Replace(sql, indexText, valueText),
			args...);	
	}
};

template <int TIndex, typename T, typename... TArgs>
class SqlCommandBuilder<TIndex, std::vector<T>, TArgs...>
{
public:
	static std::string Build(
		pqxx::work& transaction,
		const std::string& sql,
		std::vector<T> arg,
		TArgs... args)
	{
		if (arg.empty())
			throw std::runtime_error("SQL in clause must have at least one element.");
		std::vector<std::string> quotedStrings;
		std::transform(
			arg.begin(),
			arg.end(),
			std::back_inserter(quotedStrings),
			[&](const std::string& value){ return transaction.quote(value); });
		auto indexText = "{" + std::to_string(TIndex) + "}";
		auto valueText = String::Join(quotedStrings, ",");
		return SqlCommandBuilder<TIndex + 1, TArgs...>::Build(
			transaction,
			String::Replace(sql, indexText, valueText),
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
