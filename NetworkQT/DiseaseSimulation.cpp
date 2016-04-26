#include "stdafx.h"
#include "DiseaseSimulation.h"
#include "HNAGraphFactory.h"


DiseaseSimulation::DiseaseSimulation()
{

}

DiseaseSimulation::DiseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseOptions& options) : 
options_(options),
Simulation(std::move(HNAGraphFactory::sharedFactory()->getGraph(g_options)))
{
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		HNAGraph::Vertex cur = *vp.first;
		bool male = RandomManager::sharedManager()->event(0.5);
		if (male)
			(*graph_p_).properties(cur).sex_ = HNAGraph::HNANodeBundle::Sex::Male;
		else
			(*graph_p_).properties(cur).sex_ = HNAGraph::HNANodeBundle::Sex::Female;
	}
}

DiseaseSimulation::~DiseaseSimulation()
{
}
