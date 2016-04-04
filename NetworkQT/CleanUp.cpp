#include "stdafx.h"
#include "CleanUp.h"
#include "FileManager.h"
#include "TimeManager.h"
#include "GraphManager.h"
#include "DefaultNotificationCenter.h"
#include "HNAGraphFactory.h"
#include "BroadcastFinishSchemeFactory.h"
#include "BroadcastReceiveSchemeFactory.h"
#include "BroadcastSendSchemeFactory.h"
#include "RandomManager.h"


CleanUp::CleanUp()
{
}


CleanUp::~CleanUp()
{
}


void CleanUp::cleanUp()
{
	FileManager::release();
	TimeManager::release();
	GraphManager::release();
	DefaultNotificationCenter::release();
	HNAGraphFactory::release();
	BroadcastFinishSchemeFactory::release();
	BroadcastReceiveSchemeFactory::release();
	BroadcastSendSchemeFactory::release();
	RandomManager::release();
}