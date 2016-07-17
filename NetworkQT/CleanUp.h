#pragma once
#include "FileManager.h"
#include "TimeManager.h"
#include "HNAGraphFactory.h"
#include "GraphManager.h"

class CleanUp
{
private:
	CleanUp();
	~CleanUp();
public:
	static void cleanUp();
};

