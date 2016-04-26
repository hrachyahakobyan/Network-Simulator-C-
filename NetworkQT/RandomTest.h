#pragma once
#include "SimTest.h"
class RandomTest : public SimTest
{
public:
	RandomTest();
	~RandomTest();
	void test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top);
};

