#pragma once
#include "SqlCommandBuilder.h"
#include <string>
#include <pqxx/pqxx>

class SqlCommand
{
public:
	SqlCommand()
		: connection("dbname=sheepshead"), transaction(connection)
	{
	}
	
	template <typename... TArgs>
	pqxx::result Execute(const std::string& sql, TArgs... args)
	{
		return transaction.exec(SqlCommandBuilder<0, TArgs...>::Build(transaction, sql, args...));
	}
	
	void Commit()
	{
		transaction.commit();
	}
	
private:
	pqxx::connection connection;
	pqxx::work transaction;
};

