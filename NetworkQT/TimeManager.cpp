#include "stdafx.h"
#include "TimeManager.h"

TimeManager *TimeManager::timeManager = 0;

TimeManager::~TimeManager()
{

}

std::string TimeManager::date_string()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y-%H-%M-%S", &tstruct);
	return buf;
}


