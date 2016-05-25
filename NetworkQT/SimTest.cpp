#include "stdafx.h"
#include "SimTest.h"


SimTest::SimTest() : isRunning_(false), isCancelled_(false)
{
}


SimTest::~SimTest()
{
}

void SimTest::cancel()
{
	isCancelled_ = true;
}