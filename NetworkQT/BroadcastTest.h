#pragma once
#include "SimTest.h"
#include "FileManager.h"
#include <chrono>

class BroadcastTest : public SimTest
{
public:
	BroadcastTest();
	~BroadcastTest();
	void test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top, SimTestCallBack* callback = 0);
};
