#include "stdafx.h"
#include "DiseaseSimulationSIR.h"
#include "RandomManager.h"


DiseaseSimulationSIR::DiseaseSimulationSIR(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options) :
DiseaseSimulation(g_options, options)									
{
}

DiseaseSimulationSIR::~DiseaseSimulationSIR()
{
}

bool DiseaseSimulationSIR::tick(int count)
{
	using namespace std;
	typedef HNAGraph::HNANodeBundle Message;
	typedef HNAGraph::Vertex Vertex;
	typedef map<HNAGraph::Vertex, Message> s_m_map;
	typedef map<HNAGraph::Vertex, s_m_map> r_m_map;
	typedef s_m_map::iterator s_m_it;
	typedef r_m_map::iterator r_m_it;

	s_m_map s_map;
	r_m_map r_map;
	for (int round = 0; round < count; round++)
	{
		if (finished())
		{
			return true;
		}
		HNAGraph::Vertex_Range vp;
		r_map.clear();

		/* Send messages */
		for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
		{
			s_map.clear();
			Vertex cur_v = *vp.first;
			send(cur_v, s_map);
			s_m_it s_it;
			for (s_it = s_map.begin(); s_it != s_map.end(); ++s_it)
			{
				r_map[(*s_it).first][cur_v] = (*s_it).second;
			}
		}
		/* Receive messages */
		for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
		{
			Vertex cur_v = *vp.first;
			receive(cur_v, r_map[cur_v]);
		}
		/* Iterate over infected */
		for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
		{
			Vertex cur_v = *vp.first;
			Message* prop = &((*graph_p_).properties(cur_v));
			if (prop->state_ == SIR_States::Infected)
			{
				if (prop->inf_preiod_ == 0)
					(*graph_p_).properties(cur_v).state_ = SIR_States::Recovered;
				else
					(*graph_p_).properties(cur_v).inf_preiod_ -= 1;
			}
		}
	}
	return false;
}

bool DiseaseSimulationSIR::finished() const
{
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		HNAGraph::Vertex cur_v = *vp.first;
		if ((*graph_p_).properties(cur_v).state_ != SIR_States::Recovered)
			return false;
	}
	return true;
}


void DiseaseSimulationSIR::send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) 
{
	messages.clear();
	if ((*graph_p_).properties(sender).state_ != SIR_States::Infected)
		return;
	HNAGraph::Adjacency_Range adj_v = (*graph_p_).getAdjacentVertices(sender);
	for (; adj_v.first != adj_v.second; ++adj_v.first)
	{
		HNAGraph::Vertex cur_v = *(adj_v.first);
		HNAGraph::HNANodeBundle cur_v_prop = (*graph_p_).properties(cur_v);
		if (cur_v_prop.state_ == SIR_States::Suspectible)
		{
			bool infect = RandomManager::sharedManager()->event(inf_rate_);
			if (infect)
			{
				HNAGraph::HNANodeBundle message;
				message.state_ = SIR_States::Infected;
				message.inf_preiod_ = inf_period_;
				messages.insert(std::make_pair(cur_v, message));
			}
		}
	}
}


void DiseaseSimulationSIR::receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) 
{
	typedef std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>::const_iterator map_it;
	map_it it;
	for (it = messages.begin(); it != messages.end(); ++it)
	{
		const HNAGraph::HNANodeBundle* m = &((*it).second);
		assert(m->state_ > -1 && "ERROR: BroadcastReceiveSchemeM1: vertex has negative state");
		if (m->state_ == SIR_States::Infected)
		{
			(*graph_p_).properties(node).state_ = SIR_States::Infected;
			(*graph_p_).properties(node).inf_preiod_ = m->inf_preiod_;
			break;
		}
	}
}
