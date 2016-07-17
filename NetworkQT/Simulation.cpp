#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation()
{
}


Simulation::~Simulation()
{
	graph_p_.reset();
}

const HNAGraph& Simulation::state() const
{
	return (*graph_p_);
}

bool Simulation::finish(int max_ticks )
{
	assert(max_ticks > 0 && "ERROR: BroadcastAlgorithm: nonpositive max_ticks");
	while (!tick(1) && max_ticks >= 0)
	{
		max_ticks--;
		if (max_ticks < 0)
		{
			std::cout << "Broadcasting could not be finished with " << max_ticks << " ticks \n";
			return false;
		}
	}
	return true;
}

int Simulation::edgeCount() const
{
	return (*graph_p_).edge_count();
}

int Simulation::vertexCount() const
{
	return (*graph_p_).vertex_count();
}

void Simulation::edit(const GraphEditAction& edit)
{
	switch (edit.type_)
	{
	case GraphEditAction::EditType::AddEdge:
	{
		(*graph_p_).add_edge(edit.src_, edit.targ_);
	}
	break;
	case GraphEditAction::EditType::AddVertex:
	{
		(*graph_p_).add_vertex();
		if (edit.state_ >= 0)
			(*graph_p_).properties((*graph_p_).vertex_count() - 1).state_ = edit.state_;
	}
	break;
	case GraphEditAction::EditType::DeleteEdge:
	{
		(*graph_p_).remove_edge(edit.src_, edit.targ_);
	}
	break;
	case GraphEditAction::EditType::DeleteVertex:
	{
		(*graph_p_).remove_vertex(edit.v_);
	}
	break;
	case GraphEditAction::EditType::SetState:
	{
		if (edit.state_ >= 0)
			(*graph_p_).properties(edit.v_).state_ = edit.state_;
	}
	break;
	}
}

std::map<std::string, std::pair<Color, std::vector<int>>> Simulation::data()
{
	return data_;
}


void Simulation::reset()
{
	/*Reset vertex states*/
	HNAGraph::Vertex_Range vp = (*graph_p_).vertices();
	for (; vp.first != vp.second; ++vp.first)
	{
		(*graph_p_).properties(*vp.first).state_ = 0;
	}
	(*graph_p_).properties().broadcast_time_ = 0;
	initializeData();
}