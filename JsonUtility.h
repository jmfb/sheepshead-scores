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
	
	inline std::string ToObject(const std::string& value)
	{
		return "\"" + EscapeJson(value) + "\"";
	}
	
	inline std::string ToJson(int value)
	{
		return "\"" + std::to_string(value) + "\"";
	}
	
	inline std::string ToObject(int value)
	{
		return std::to_string(value);
	}
	
	inline std::string ToObject(bool value)
	{
		return value ? "true" : "false";
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
	
	template <typename T>
	std::string ToObject(const std::vector<T>& value)
	{
		std::ostringstream out;
		out << "[";
		for (auto iter = value.begin(); iter != value.end(); ++iter)
		{
			if (iter != value.begin())
				out << ",";
			out << ToObject(*iter);
		}
		out << "]";
		return out.str();
	}
	
	class IWriter
	{
	public:
		virtual std::string ToJson() const { return ""; };
		virtual std::string ToObject() const { return ""; };
	};
	
	inline std::string ToObject(const IWriter& value)
	{
		return value.ToObject();
	}
	
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
		static std::string JsonifyObject(const char* name, const T& value, TArgs... args)
		{
			std::ostringstream out;
			if (TIndex > 0)
				out << ",";
			out << name << ":" << ToObject(value);
			out << JsonWriter<TIndex + 1, TArgs...>::JsonifyObject(args...);
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
		static std::string JsonifyObject()
		{
			return {};
		}
	};
	
	template <typename... TArgs>
	std::string Jsonify(TArgs... args)
	{
		return "{" + JsonWriter<0, TArgs...>::Jsonify(args...) + "}";
	}
	
	template <typename... TArgs>
	std::string JsonifyObject(TArgs... args)
	{
		return "{" + JsonWriter<0, TArgs...>::JsonifyObject(args...) + "}";
	}	
	
	template <typename T>
	HttpResponse Content(const T& model)
	{
		return { "application/json", ToJson(model) };
	}
}

