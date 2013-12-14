#pragma once
#include "BaseController.h"
#include "PlayerScoreModel.h"
#include <string>
#include <vector>

class Controller : public BaseController
{
public:
	virtual HttpResponse Execute();

private:	
	HttpResponse Index();
	HttpResponse LookupNames(const std::string& query);
	HttpResponse SubmitScores(const std::vector<PlayerScoreModel>& playerScores);
};

