#pragma once
#include "Simulation.h"
class DiseaseSimulation : public Simulation
{
public:
	DiseaseSimulation();
	DiseaseSimulation(graph_ptr g, double ir, int ip);
	virtual ~DiseaseSimulation();
	virtual bool tick(int count = 1) = 0;
	virtual bool finish(int max_ticks = MAX_TICKS) = 0;
	virtual bool finished() const = 0;
	virtual void edit(const GraphEditAction& edit) = 0;
protected:
	const double inf_rate_;
	const int inf_period_;
};

