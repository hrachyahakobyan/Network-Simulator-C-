#pragma once
#include "Simulation.h"
class DiseaseSimulation : public Simulation
{
public:
	enum ModelType{ SIR, SIS, SIRS };
	struct DiseaseOptions
	{
		ModelType type;
		double inf_rate_;
		int inf_period_;
	};
public:
	DiseaseSimulation();
	DiseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	virtual ~DiseaseSimulation();
	virtual bool tick(int count = 1) = 0;
	virtual bool finished() const = 0;
protected:
	const double inf_rate_;
	const int inf_period_;
};

