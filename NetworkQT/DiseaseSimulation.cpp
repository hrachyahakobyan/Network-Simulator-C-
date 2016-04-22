#include "stdafx.h"
#include "DiseaseSimulation.h"
#include "HNAGraphFactory.h"


DiseaseSimulation::DiseaseSimulation() : inf_rate_(0), inf_period_(1)
{

}

DiseaseSimulation::DiseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseOptions& options) : 
inf_rate_(options.inf_rate_), inf_period_(options.inf_period_),
Simulation(std::move(HNAGraphFactory::sharedFactory()->getGraph(g_options)))
{

}

DiseaseSimulation::~DiseaseSimulation()
{
}
