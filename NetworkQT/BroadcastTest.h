#pragma once
#include "SimTest.h"

class BroadcastTest : public SimTest
{
public:
	BroadcastTest();
	~BroadcastTest();
	void test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top, Progress_F f = 0);
};
