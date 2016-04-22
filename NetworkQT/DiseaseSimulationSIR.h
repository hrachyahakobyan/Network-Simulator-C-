#pragma once
#include "DiseaseSimulation.h"
class DiseaseSimulationSIR : public DiseaseSimulation
{
public:
	DiseaseSimulationSIR(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	~DiseaseSimulationSIR();
	virtual bool tick(int count = 1);
	virtual bool finished() const;
private:
	void send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) ;
	void receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) ;
	
private:
	enum SIR_States{Suspectible, Infected, Recovered};
};

