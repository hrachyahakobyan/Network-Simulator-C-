#pragma once
#include "DiseaseSimulationSIR.h"
#include "SimTest.h"
#include "DiseaseSimulationSIS.h"
#include "DiseaseSimulationSIRS.h"

class DiseaseTest
{
public:
	DiseaseTest();
	~DiseaseTest();
	void test(const GraphBuilder::GraphOptions& gop, const DiseaseSimulation::DiseaseOptions& dop, const TestOptions& top);
};

