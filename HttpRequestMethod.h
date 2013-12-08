#pragma once

enum class HttpRequestMethod
{
	Get,
	Post,
	Other
};

HttpRequestMethod GetRequestMethod();

