#pragma once
#include "BaseController.h"
#include "PlayerScoreModel.h"
#include "FileUploadData.h"
#include <string>
#include <vector>

class Controller : public BaseController
{
public:
	virtual HttpResponse Execute();

private:
	bool IsAction(const std::string& name) const;

	HttpResponse Index();
	HttpResponse LookupNames(const std::string& query);
	HttpResponse SubmitScores(const std::vector<PlayerScoreModel>& playerScores);
	HttpResponse ReportMTD();
	HttpResponse ReportYTD();
	HttpResponse ReportHistory();
	HttpResponse UploadScores();
	HttpResponse UploadScores(const FileUploadData& fileUpload);
};

