#pragma once
#include "DiseaseSimulation.h"
class DiseaseSimulationSIR : public DiseaseSimulation
{
public:
	 DiseaseSimulationSIR(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	~DiseaseSimulationSIR();
	virtual bool tick(int count = 1);
	virtual bool finished() const;
	virtual void edit(const GraphEditAction& edit);
	virtual std::string description() const;
	virtual std::map<std::string, int> allowedStates() const;
protected:
	virtual void send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) ;
	virtual void receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) ;
	virtual void iterate();
protected:
	enum SIR_States{Suspectible, Infected, Recovered};
protected:
	virtual void updateData();
	virtual void initializeData();
};

