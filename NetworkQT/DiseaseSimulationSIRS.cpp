#include "stdafx.h"
#include "DiseaseSimulationSIRS.h"


DiseaseSimulationSIRS::DiseaseSimulationSIRS(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options) :
DiseaseSimulationSIR(g_options, options)
{
}


DiseaseSimulationSIRS::~DiseaseSimulationSIRS()
{
}

std::string DiseaseSimulationSIRS::description() const
{
	std::string desc("SIRS");
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
	if (options_.imType_ == Options::ImmunityType::Fixed)
	{
		desc.append(". Immunity period = ");
		desc.append(std::to_string(options_.imm_period_));
	}
	else
	{
		desc.append(". Immunity loss rate = ");
		desc.append(std::to_string(options_.imm_loss_rate_));
	}
	return desc;
}

void DiseaseSimulationSIRS::edit(const GraphEditAction& edit)
{
	DiseaseSimulationSIR::edit(edit);
	if (edit.type_ == GraphEditAction::EditType::AddVertex)
	{
		if (edit.state_ == SIR_States::Recovered && options_.imType_ == Options::ImmunityType::Fixed)
		{
			(*graph_p_).properties((*graph_p_).vertex_count() - 1).imm_period_ = options_.imm_period_;
		}
	}
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

		iterate();
		/* Send messages */
		for (vp = (*graph_p_).vertices(); vp.first != vp.second; ++vp.first)
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
		for (vp = (*graph_p_).vertices(); vp.first != vp.second; ++vp.first)
		{
			Vertex cur_v = *vp.first;
			receive(cur_v, r_map[cur_v]);
		}
		/* Iterate over infected */

		updateData();
	}
	return false;
}


void DiseaseSimulationSIRS::iterate()
{
	typedef HNAGraph::HNANodeBundle Message;
	typedef HNAGraph::Vertex Vertex;
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).vertices(); vp.first != vp.second; ++vp.first)
	{
		Vertex cur_v = *vp.first;
		Message* prop = &((*graph_p_).properties(cur_v));
		if (prop->state_ == SIR_States::Infected)
		{
			if (options_.infType_ == Options::InfectionType::Fixed)
			{
				if (prop->inf_preiod_ == 0)
					(*graph_p_).properties(cur_v).state_ = SIR_States::Recovered;
				else
					(*graph_p_).properties(cur_v).inf_preiod_ -= 1;
			}
			else
			{
				bool changeState = RandomManager::sharedManager()->event(options_.rec_rate_);
				if (changeState)
				{
					(*graph_p_).properties(cur_v).state_ = SIR_States::Recovered;
				}
			}
		}
		else if (prop->state_ == SIR_States::Recovered)
		{
			if (options_.imType_ == Options::ImmunityType::Fixed)
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
			else
			{
				double changeState = RandomManager::sharedManager()->event(options_.imm_loss_rate_);
				if (changeState)
				{
					(*graph_p_).properties(cur_v).state_ = SIR_States::Suspectible;
				}
			}
		}
	}
}

void DiseaseSimulationSIRS::updateData()
{
	std::map<int, std::pair<Color, int>> data;
	data[SIR_States::Infected] = std::pair<Color, int>(Color::Black, 0);
	data[SIR_States::Recovered] = std::pair<Color, int>(Color::Green, 0);
	data[SIR_States::Suspectible] = std::pair<Color, int>(Color::White, 0);
	int infected = 0;
	int recovered = 0;
	int susceptible = 0;
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).vertices(); vp.first != vp.second; ++vp.first)
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
	data_["Immune"].second.push_back(recovered);
}

void DiseaseSimulationSIRS::initializeData()
{
	data_["Infected"] = std::make_pair(Color::Black, std::vector<int>());
	data_["Immune"] = std::make_pair(Color::Green, std::vector<int>());
	data_["Susceptible"] = std::make_pair(Color::Blue, std::vector<int>());
}