#pragma once
#include "HttpResponse.h"
#include <string>
#include <sstream>

class BaseView
{
public:
	BaseView() = default;
	BaseView(const BaseView& rhs) = delete;
	~BaseView() = default;
	
	BaseView& operator=(const BaseView& rhs) = delete;
	
	std::string Render();

	virtual void RenderBody();
	
	void Write(const std::string& value);

private:
	std::ostringstream content;
};

template <typename TView>
inline HttpResponse View(int statusCode = 0)
{
	TView view;
	return { "text/html", view.Render(), statusCode };
}

template <typename TView, typename TModel>
inline HttpResponse View(const TModel& model, int statusCode = 0)
{
	TView view;
	view.SetModel(model);
	return { "text/html", view.Render(), statusCode };
}

