#pragma once
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
inline std::string RenderView()
{
	TView view;
	return view.Render();
}

template <typename TView, typename TModel>
inline std::string RenderView(const TModel& model)
{
	TView view;
	view.SetModel(model);
	return view.Render();
}

