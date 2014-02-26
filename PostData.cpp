#include "PostData.h"
#include "HttpContext.h"

PostData::PostData()
	: FormData(HttpContext::ReadPostDataOfType(ContentTypes::Form))
{
}

