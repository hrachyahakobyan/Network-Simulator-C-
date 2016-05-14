#include "stdafx.h"
#include "DiseaseSimulationSIS.h"


DiseaseSimulationSIS::DiseaseSimulationSIS(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options) :
DiseaseSimulation(g_options, options)
{
	(*graph_p_).properties().broadcast_type_ = description();
	initializeData();
	updateData();
}

DiseaseSimulationSIS::~DiseaseSimulationSIS()
{
}

std::map<std::string, int> DiseaseSimulationSIS::allowedStates() const
{
	return std::map<std::string, int>({ {"Susceptible" , 0}, {"Infected", 1 } });
}

std::string DiseaseSimulationSIS::description() const
{
	std::string desc("SIS");
	desc.append(". Infection rate = ");
	desc.append(std::to_string(options_.inf_rate_));
	if (options_.infType_ == Options::InfectionType::Fixed)
	{
		desc.append(". Infection period = ");
		desc.append(std::to_string(options_.inf_period_));
	}
	else
	{
		desc.append(". Recovery rate = ");
		desc.append(std::to_string(options_.rec_rate_));
	}

	return desc;
}

bool DiseaseSimulationSIS::tick(int count)
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
		iterate();
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
	
		updateData();
	}
	return false;
}

void DiseaseSimulationSIS::iterate()
{
	typedef HNAGraph::HNANodeBundle Message;
	typedef HNAGraph::Vertex Vertex;
	HNAGraph::Vertex_Range vp;
	/* Iterate over infected */
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		Vertex cur_v = *vp.first;
		Message* prop = &((*graph_p_).properties(cur_v));
		if (prop->state_ == SIS_States::Infected)
		{
			if (options_.infType_ == Options::InfectionType::Fixed)
			{
				if (prop->inf_preiod_ == 0)
					(*graph_p_).properties(cur_v).state_ = SIS_States::Suspectible;
				else
					(*graph_p_).properties(cur_v).inf_preiod_ -= 1;
			}
			else
			{
				bool changeState = RandomManager::sharedManager()->event(options_.rec_rate_);
				if (changeState)
				{
					(*graph_p_).properties(cur_v).state_ = SIS_States::Suspectible;
				}
			}

		}
	}
}

bool DiseaseSimulationSIS::finished() const
{
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		HNAGraph::Vertex cur_v = *vp.first;
		if ((*graph_p_).properties(cur_v).state_ == SIS_States::Infected)
			return false;
	}
	return true;
}


void DiseaseSimulationSIS::send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages)
{
	typedef DiseaseSimulation::DiseaseOptions::Sex Sex;
	messages.clear();
	if ((*graph_p_).properties(sender).state_ != SIS_States::Infected)
		return;
	HNAGraph::Adjacency_Range adj_v = (*graph_p_).getAdjacentVertices(sender);
	for (; adj_v.first != adj_v.second; ++adj_v.first)
	{
		HNAGraph::Vertex cur_v = *(adj_v.first);
		HNAGraph::HNANodeBundle cur_v_prop = (*graph_p_).properties(cur_v);
		if (cur_v_prop.state_ == SIS_States::Suspectible)
		{
			Sex senderSex = (*graph_p_).properties(sender).sex_;
			Sex receiverSex = (*graph_p_).properties(cur_v).sex_;
			double coeff = options_.sexCoeffMap_[senderSex][receiverSex];
			double rate = options_.inf_rate_ * coeff;
			bool infect = RandomManager::sharedManager()->event(rate);
			if (infect)
			{
				HNAGraph::HNANodeBundle message;
				message.state_ = SIS_States::Infected;
				if (options_.infType_ == Options::InfectionType::Fixed)
					message.inf_preiod_ = options_.inf_period_;
				messages.insert(std::make_pair(cur_v, message));
			}
		}
	}
}


void DiseaseSimulationSIS::receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages)
{
	typedef std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>::const_iterator map_it;
	map_it it;
	for (it = messages.begin(); it != messages.end(); ++it)
	{
		const HNAGraph::HNANodeBundle* m = &((*it).second);
		if (m->state_ == SIS_States::Infected)
		{
			(*graph_p_).properties(node).state_ = SIS_States::Infected;
			if (options_.infType_ == Options::InfectionType::Fixed)
				(*graph_p_).properties(node).inf_preiod_ = m->inf_preiod_;
			break;
		}
	}
}

void DiseaseSimulationSIS::edit(const GraphEditAction& edit)
{
	Simulation::edit(edit);
	if (edit.type_ == GraphEditAction::EditType::AddVertex)
	{
		if (edit.state_ == SIS_States::Infected)
		{
			(*graph_p_).properties((*graph_p_).getVertexCount() - 1).inf_preiod_ = options_.inf_period_;
		}
	}
	else if (edit.type_ == GraphEditAction::EditType::SetState)
	{
		if (edit.state_ == SIS_States::Infected)
		{
			(*graph_p_).properties(edit.v_).inf_preiod_ = options_.inf_period_;
		}
	}
}

void DiseaseSimulationSIS::updateData()
{
	std::map<std::string, std::pair<Color, int>> data;
	data["Infected"] = std::pair<Color, int>(Color::Red, 0);
	data["Susceptible"] = std::pair<Color, int>(Color::White, 0);
	std::map<int, std::string> stateMap;
	stateMap[SIS_States::Infected] = "Infected";
	stateMap[SIS_States::Suspectible] = "Susceptible";
	int infected = 0;
	int susceptible = 0;
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		int state = (*graph_p_).properties(*vp.first).state_;
		if (state == SIS_States::Infected)
		{
			infected++;
		}
		else
		{
			susceptible++;
		}
	}
	data_["Susceptible"].second.push_back(susceptible);
	data_["Infected"].second.push_back(infected);
}

void DiseaseSimulationSIS::initializeData()
{
	data_["Infected"] = std::make_pair(Color::Red, std::vector<int>());
	data_["Susceptible"] = std::make_pair(Color::Blue, std::vector<int>());
}