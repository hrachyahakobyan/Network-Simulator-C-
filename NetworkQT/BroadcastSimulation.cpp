#include "stdafx.h"
#include "BroadcastSimulation.h"

using namespace std;

BroadcastSimulation::~BroadcastSimulation()
{
	scheme_p_.reset();
}


bool BroadcastSimulation::tick(int count)
{
	assert(count > 0 && "ERROR: BroadcastAlgorithm: nonpositive tick");
	typedef HNANodeBundle Message;
	typedef map<Vertex, Message> s_m_map;
	typedef map<Vertex, s_m_map> r_m_map;
	typedef s_m_map::iterator s_m_it;
	typedef r_m_map::iterator r_m_it;

	s_m_map s_map;
	r_m_map r_map;
	s_m_map final_map;
	for (int round = 0; round < count; round++)
	{
		if ((*scheme_p_).broadcasting_finished(g_))
		{
			cout << "Broadcasting has finished " << endl;
			return true;
		}
		g_.properties().broadcast_time_++;
		pair<vertex_iter, vertex_iter> vp;
		r_map.clear();
		final_map.clear();
		for (vp = boost::vertices(g_.g_container); vp.first != vp.second; ++vp.first)
		{
			s_map.clear();
			Vertex cur_v = *vp.first;
			(*scheme_p_).send(g_, cur_v, s_map);
			s_m_it s_it;
			for (s_it = s_map.begin(); s_it != s_map.end(); ++s_it)
			{
				r_map[(*s_it).first][cur_v] = (*s_it).second;
			}
		}
		for (vp = boost::vertices(g_.g_container); vp.first != vp.second; ++vp.first)
		{
			Vertex cur_v = *vp.first;
			Message m;
			(*scheme_p_).receive(g_, cur_v, r_map[cur_v], m);
			final_map[cur_v] = m;
		}
		// apply r_m_map
		s_m_it final_it;
		for (final_it = final_map.begin(); final_it != final_map.end(); ++final_it)
		{
			g_.properties((*final_it).first) = (*final_it).second;
		}
	}
	return false;
}


bool BroadcastSimulation::finish(int max_ticks)
{
	assert(max_ticks > 0 && "ERROR: BroadcastAlgorithm: nonpositive max_ticks");
	while (!tick(1) && max_ticks >= 0)
	{
		max_ticks--;
		if (max_ticks < 0)
		{
			cout << "Broadcasting could not be finished with " << max_ticks << " ticks \n";
			return false;
		}
	}
	return true;
}


bool BroadcastSimulation::finished() const
{
	return (*scheme_p_).broadcasting_finished(g_);
}


const HNAGraph& BroadcastSimulation::state() const
{
	return g_;
}


void BroadcastSimulation::add_vertex()
{
	g_.AddVertex();
}


void BroadcastSimulation::add_edge(int source, int target)
{
	g_.AddEdge(source, target);
}

void BroadcastSimulation::delete_edge(int source, int target)
{
	g_.RemoveEdge(source, target);
}

void BroadcastSimulation::delete_vertex(int vertex)
{
	g_.RemoveVertex(vertex);
}


void BroadcastSimulation::set_state(int vertex, int state)
{
	assert(vertex > -1 && "ERROR: BroadcastSimulation: set_state: negative vertex index");
	assert(state > -1 && "ERROR: BroadcastSimulation: set_state: negative state");
	g_.properties(vertex).state_ = state;
	std::cout << "new state  " << g_.properties(vertex).state_ << std::endl;
}
