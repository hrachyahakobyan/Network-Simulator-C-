#pragma once
#include "DiseaseSimulationSIR.h"
class DiseaseSimulationSIRS : public DiseaseSimulationSIR
{
public:
	DiseaseSimulationSIRS(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	~DiseaseSimulationSIRS();
	virtual bool tick(int count = 1);
	virtual std::string description() const;
	void edit(const GraphEditAction& edit);
protected:
	void iterate();
	void updateData();
	void initializeData();
};

