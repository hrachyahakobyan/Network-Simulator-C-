#pragma once
#include "DiseaseSimulation.h"
class DiseaseSimulationSIR : public DiseaseSimulation
{
public:
	DiseaseSimulationSIR(graph_ptr g, double ir, int ip);
	~DiseaseSimulationSIR();
	virtual bool tick(int count = 1) = 0;
	virtual bool finish(int max_ticks = MAX_TICKS) = 0;
	virtual bool finished() const = 0;
	virtual void edit(const GraphEditAction& edit) = 0;
};

