#include "stdafx.h"
#include "DiseaseSimulationSIR.h"


DiseaseSimulationSIR::DiseaseSimulationSIR(graph_ptr g, double ir, int ip) : 
DiseaseSimulation(std::move(g), ir, ip)									
{
}

DiseaseSimulationSIR::~DiseaseSimulationSIR()
{
}

bool DiseaseSimulationSIR::tick(int count)
{
	return true;
}

bool DiseaseSimulationSIR::finish(int max_ticks)
{
	return false;
}

bool DiseaseSimulationSIR::finished() const
{
	return false;
}

void DiseaseSimulationSIR::edit(const GraphEditAction& edit)
{

}