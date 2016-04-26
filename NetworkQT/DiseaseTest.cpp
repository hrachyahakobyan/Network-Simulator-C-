#include "stdafx.h"
#include "DiseaseTest.h"


DiseaseTest::DiseaseTest()
{
}


DiseaseTest::~DiseaseTest()
{
}


void DiseaseTest::test(const GraphBuilder::GraphOptions& gop, const DiseaseSimulation::DiseaseOptions& dop, const TestOptions& top)
{
	if (gop.type_ != GraphBuilder::GraphOptions::GraphType::Graph_ScaleFreeRandom)
		return;

}