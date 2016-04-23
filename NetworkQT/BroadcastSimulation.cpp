#include "stdafx.h"
#include "BroadcastSimulation.h"

using namespace std;

BroadcastSimulation::~BroadcastSimulation()
{
	scheme_p_.reset();
	graph_p_.reset();
}


std::string BroadcastSimulation::description() const
{
	return (*scheme_p_).description();
}

bool BroadcastSimulation::tick(int count)
{
	assert(count > 0 && "ERROR: BroadcastAlgorithm: nonpositive tick");
	typedef HNAGraph::HNANodeBundle Message;
	typedef map<HNAGraph::Vertex, Message> s_m_map;
	typedef map<HNAGraph::Vertex, s_m_map> r_m_map;
	typedef s_m_map::iterator s_m_it;
	typedef r_m_map::iterator r_m_it;

	s_m_map s_map;
	r_m_map r_map;
	s_m_map final_map;
	for (int round = 0; round < count; round++)
	{
		if ((*scheme_p_).broadcasting_finished(*graph_p_))
		{
			cout << "Broadcasting has finished " << endl;
			return true;
		}
		(*graph_p_).properties().broadcast_time_++;
		pair<HNAGraph::Vertex_Iter, HNAGraph::Vertex_Iter> vp;
		r_map.clear();
		final_map.clear();
		for (vp = boost::vertices((*graph_p_).g_container); vp.first != vp.second; ++vp.first)
		{
			s_map.clear();
			HNAGraph::Vertex cur_v = *vp.first;
			(*scheme_p_).send((*graph_p_), cur_v, s_map);
			s_m_it s_it;
			for (s_it = s_map.begin(); s_it != s_map.end(); ++s_it)
			{
				r_map[(*s_it).first][cur_v] = (*s_it).second;
			}
		}
		for (vp = boost::vertices((*graph_p_).g_container); vp.first != vp.second; ++vp.first)
		{
			HNAGraph::Vertex cur_v = *vp.first;
			Message m;
			(*scheme_p_).receive((*graph_p_), cur_v, r_map[cur_v], m);
			final_map[cur_v] = m;
		}
		// apply r_m_map
		s_m_it final_it;
		for (final_it = final_map.begin(); final_it != final_map.end(); ++final_it)
		{
			(*graph_p_).properties((*final_it).first) = (*final_it).second;
		}
		updateData();
	}
	return false;
}


bool BroadcastSimulation::finished() const
{
	return (*scheme_p_).broadcasting_finished((*graph_p_));
}


void BroadcastSimulation::updateData()
{
	int informed = 0;
	int uninformed = 0;
	HNAGraph::Vertex_Range vp;
	for (vp = (*graph_p_).getVertices(); vp.first != vp.second; ++vp.first)
	{
		int state = (*graph_p_).properties(*vp.first).state_;
		if (state == Two_State::informed)
		{
			informed++;
		}
		else
		{
			uninformed++;
		}
	}
	data_["Informed"].second.push_back(informed);
	data_["Uninformed"].second.push_back(uninformed);
}

void BroadcastSimulation::initializeData()
{
	data_["Informed"] = std::make_pair(Color::Black, std::vector<int>());
	data_["Uninformed"] = std::make_pair(Color::Blue, std::vector<int>());
}