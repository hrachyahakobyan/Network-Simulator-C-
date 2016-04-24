#include "stdafx.h"
#include "DiseaseSimulation.h"
#include "HNAGraphFactory.h"


DiseaseSimulation::DiseaseSimulation()
{

}

DiseaseSimulation::DiseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseOptions& options) : 
options_(options),
Simulation(std::move(HNAGraphFactory::sharedFactory()->getGraph(g_options)))
{

}

DiseaseSimulation::~DiseaseSimulation()
{
}
