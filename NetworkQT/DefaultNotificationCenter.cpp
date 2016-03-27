#include "stdafx.h"
#include "DefaultNotificationCenter.h"

DefaultNotificationCenter *DefaultNotificationCenter::sharedNotificationCenter = 0;
int SomeObserver::count = 0;


DefaultNotificationCenter::DefaultNotificationCenter()
{
}


DefaultNotificationCenter::~DefaultNotificationCenter()
{
	observerMap.clear();
}


void DefaultNotificationCenter::addObserver(Observer* _observer, const std::string &_notificationName)
{
	if (!_observer)
		return;
	if (observerMap.find(_notificationName) == observerMap.end())
	{
		std::set<Observer*> set;
		set.insert(_observer);
		std::pair<std::string, std::set<Observer*>> pair(_notificationName, set);
		observerMap.insert(pair);
	}
	else
	{
		observerMap[_notificationName].insert(_observer);
	}
}

void DefaultNotificationCenter::removeObserver(Observer* const _observer, const std::string &_notificationName)
{
	if (!_observer)
		return;
	if (observerMap.find(_notificationName) == observerMap.end())
		return;
	else
	{
		observerMap[_notificationName].erase(_observer);
	}
}

void DefaultNotificationCenter::postNotification(const std::string& _notificationName)
{
	if (observerMap.find(_notificationName) == observerMap.end())
		return;
	else
	{
		std::set<Observer*>::iterator it;
		for (it = observerMap[_notificationName].begin(); it != observerMap[_notificationName].end(); ++it)
		{
			(*it)->notify(_notificationName);
		}
	}
}