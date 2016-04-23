#include "stdafx.h"
#include "DiseaseSimulationSIRS.h"


DiseaseSimulationSIRS::DiseaseSimulationSIRS(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options) :
DiseaseSimulationSIR(g_options, options), imm_period_(options.imm_period_)
{
}


DiseaseSimulationSIRS::~DiseaseSimulationSIRS()
{
}

std::string DiseaseSimulationSIRS::description() const
{
	std::string desc("SIRS");
	desc.append(". Infection rate = ");
	desc.append(std::to_string(inf_rate_));
	desc.append(". Infection period = ");
	desc.append(std::to_string(inf_period_));
	desc.append(". Immunity period = ");
	desc.append(std::to_string(imm_period_));
	return desc;
}

bool DiseaseSimulationSIRS::tick(int count)
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
		(*graph_p_).properties().broadcast_time_++;
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
				{
					(*graph_p_).properties(cur_v).state_ = SIR_States::Recovered;
					(*graph_p_).properties(cur_v).imm_period_ = imm_period_;
				}
				else
					(*graph_p_).properties(cur_v).inf_preiod_ -= 1;
			}
			else if (prop->state_ == SIR_States::Recovered)
			{
				if (prop->imm_period_ == 0)
				{
					(*graph_p_).properties(cur_v).state_ = SIR_States::Suspectible;
				}
				else
				{
					(*graph_p_).properties(cur_v).imm_period_ -= 1;
				}
			}
		}
		updateData();
	}
	return false;
}
