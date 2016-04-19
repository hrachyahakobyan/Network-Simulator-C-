#include "stdafx.h"
#include "DiseaseSimulation.h"


DiseaseSimulation::DiseaseSimulation() : inf_rate_(0), inf_period_(1)
{

}

DiseaseSimulation::DiseaseSimulation(graph_ptr g, double ir, int ip) : inf_rate_(ir), inf_period_(ip), Simulation(std::move(g))
{

}

DiseaseSimulation::~DiseaseSimulation()
{
}
