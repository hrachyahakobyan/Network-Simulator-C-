#pragma once
#include "DiseaseSimulation.h"
class DiseaseSimulationSIS : public DiseaseSimulation
{
public:
	DiseaseSimulationSIS(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	~DiseaseSimulationSIS();
	virtual bool tick(int count = 1);
	virtual bool finished() const;
	virtual void edit(const GraphEditAction& edit);
	virtual std::string description() const;
protected:
	void initializeData();
	void updateData();
	void send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages);
	void receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages);
protected:
	enum SIS_States{Suspectible, Infected};

};

