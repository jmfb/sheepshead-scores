#pragma once
#include "HttpResponse.h"
#include <string>
#include <vector>
#include <sstream>

namespace Json
{
	std::string EscapeJson(const std::string& value);

	inline std::string ToJson(const std::string& value)
	{
		return "\"" + EscapeJson(value) + "\"";
	}
	
	template <typename T>
	std::string ToJson(const std::vector<T>& value)
	{
		std::ostringstream out;
		out << "[";
		for (auto iter = value.begin(); iter != value.end(); ++iter)
		{
			if (iter != value.begin())
				out << ",";
			out << ToJson(*iter);
		}
		out << "]";
		return out.str();
	}
	
	class IWriter
	{
	public:
		virtual std::string ToJson() const = 0;
	};
	
	inline std::string ToJson(const IWriter& value)
	{
		return value.ToJson();
	}
	
	template <int TIndex, typename... TArgs>
	class JsonWriter
	{
	};
	
	template <int TIndex, typename T, typename... TArgs>
	class JsonWriter<TIndex, const char*, T, TArgs...>
	{
	public:
		static std::string Jsonify(const char* name, const T& value, TArgs... args)
		{
			std::ostringstream out;
			if (TIndex > 0)
				out << ",";
			out << "\"" << name << "\":" << ToJson(value);
			out << JsonWriter<TIndex + 1, TArgs...>::Jsonify(args...);
			return out.str();
		}
	};
	
	template <int TIndex>
	class JsonWriter<TIndex>
	{
	public:
		static std::string Jsonify()
		{
			return {};
		}
	};
	
	template <typename... TArgs>
	std::string Jsonify(TArgs... args)
	{
		return "{" + JsonWriter<0, TArgs...>::Jsonify(args...) + "}";
	}
	
	template <typename T>
	HttpResponse Content(const T& model)
	{
		return { "application/json", ToJson(model) };
	}
}

