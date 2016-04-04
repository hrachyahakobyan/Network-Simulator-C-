#include "stdafx.h"
#include "BroadcastSimulation.h"

using namespace std;

BroadcastSimulation::~BroadcastSimulation()
{
	scheme_p_.reset();
	graph_p_.reset();
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
	return (*scheme_p_).broadcasting_finished((*graph_p_));
}


const HNAGraph& BroadcastSimulation::state() const
{
	return (*graph_p_);
}


void BroadcastSimulation::edit(const GraphEditAction& edit)
{
	switch (edit.type_)
	{
		case GraphEditAction::EditType::AddEdge:
		{
			add_edge(edit.src_, edit.targ_);
		}
		break;
		case GraphEditAction::EditType::AddVertex:
		{
			add_vertex();
			if (edit.state_ > 0)
				set_state((*graph_p_).getVertexCount() - 1, edit.state_);
		}
		break;
		case GraphEditAction::EditType::DeleteEdge:
		{
			delete_edge(edit.src_, edit.targ_);
		}
		break;
		case GraphEditAction::EditType::DeleteVertex:
		{
			delete_vertex(edit.v_);
		}
		break;
		case GraphEditAction::EditType::SetState:
		{
			set_state(edit.v_, edit.state_);
		}
		break;
	}
}

void BroadcastSimulation::add_vertex()
{
	(*graph_p_).AddVertex();
}


void BroadcastSimulation::add_edge(int source, int target)
{
	(*graph_p_).AddEdge(source, target);
}

void BroadcastSimulation::delete_edge(int source, int target)
{
	(*graph_p_).RemoveEdge(source, target);
}

void BroadcastSimulation::delete_vertex(int vertex)
{
	(*graph_p_).RemoveVertex(vertex);
}


void BroadcastSimulation::set_state(int vertex, int state)
{
	assert(vertex > -1 && "ERROR: BroadcastSimulation: set_state: negative vertex index");
	assert(state > -1 && "ERROR: BroadcastSimulation: set_state: negative state");
	(*graph_p_).properties(vertex).state_ = state;
	std::cout << "new state  " << (*graph_p_).properties(vertex).state_ << std::endl;
}
