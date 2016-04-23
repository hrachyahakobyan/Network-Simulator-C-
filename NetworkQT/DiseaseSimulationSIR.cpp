#include "stdafx.h"
#include "DiseaseSimulationSIR.h"


DiseaseSimulationSIR::DiseaseSimulationSIR(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options) :
DiseaseSimulation(g_options, options)									
{
	(*graph_p_).properties().broadcast_type_ = description();
	initializeData();
	updateData();
}

DiseaseSimulationSIR::~DiseaseSimulationSIR()
{
}

std::string DiseaseSimulationSIR::description() const
{
	std::string desc("SIR");
	desc.append(". Infection rate = ");
	desc.append(std::to_string(inf_rate_));
	desc.append(". Infection period = ");
	desc.append(std::to_string(inf_period_));
	return desc;
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
					(*graph_p_).properties(cur_v).state_ = SIR_States::Recovered;
				else
					(*graph_p_).properties(cur_v).inf_preiod_ -= 1;
			}
		}
		updateData();
	}
	return false;
}

bool DiseaseSimulationSIR::finished() const
{
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		HNAGraph::Vertex cur_v = *vp.first;
		if ((*graph_p_).properties(cur_v).state_ == SIR_States::Infected)
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
		if (m->state_ == SIR_States::Infected)
		{
			(*graph_p_).properties(node).state_ = SIR_States::Infected;
			(*graph_p_).properties(node).inf_preiod_ = m->inf_preiod_;
			break;
		}
	}
}

void DiseaseSimulationSIR::edit(const GraphEditAction& edit)
{
	Simulation::edit(edit);
	if (edit.type_ == GraphEditAction::EditType::AddVertex)
	{
		if (edit.state_ == SIR_States::Infected)
		{
			(*graph_p_).properties((*graph_p_).getVertexCount() - 1).inf_preiod_ = inf_period_;
		}
	}
	else if (edit.type_ == GraphEditAction::EditType::SetState)
	{
		if (edit.state_ == SIR_States::Infected)
		{
			(*graph_p_).properties(edit.v_).inf_preiod_ = inf_period_;
		}
	}
}


void DiseaseSimulationSIR::updateData()
{
	std::map<int, std::pair<Color, int>> data;
	data[SIR_States::Infected] = std::pair<Color, int>(Color::Red, 0);
	data[SIR_States::Recovered] = std::pair<Color, int>(Color::Green, 0);
	data[SIR_States::Suspectible] = std::pair<Color, int>(Color::White, 0);
	int infected = 0;
	int recovered = 0;
	int susceptible = 0;
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		int state = (*graph_p_).properties(*vp.first).state_;
		if (state == SIR_States::Infected)
		{
			infected++;
		}
		else if (state == SIR_States::Suspectible)
		{
			susceptible++;
		}
		else
		{
			recovered++;
		}
	}
	data_["Susceptible"].second.push_back(susceptible);
	data_["Infected"].second.push_back(infected);
	data_["Recovered"].second.push_back(recovered);
}

void DiseaseSimulationSIR::initializeData()
{
	data_["Infected"] = std::make_pair(Color::Red, std::vector<int>());
	data_["Recovered"] = std::make_pair(Color::Green, std::vector<int>());
	data_["Susceptible"] = std::make_pair(Color::Blue, std::vector<int>());
}