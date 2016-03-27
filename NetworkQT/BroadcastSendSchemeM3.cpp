#include "stdafx.h"
#include "BroadcastSendSchemeM3.h"


BroadcastSendSchemeM3::BroadcastSendSchemeM3()
{
}


BroadcastSendSchemeM3::~BroadcastSendSchemeM3()
{
}

void BroadcastSendSchemeM3::send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const
{
	messages.clear();
	if (graph.properties(node).state_ == Two_State::uninformed)
		return;
	adjacency_vertex_range_t adj_v = graph.getAdjacentVertices(node);
	std::vector<Vertex> uninf_neighbors;
	for (; adj_v.first != adj_v.second; ++adj_v.first)
	{
		Vertex cur_v = *(adj_v.first);
		HNANodeBundle cur_v_prop = graph.properties(cur_v);
		uninf_neighbors.push_back(cur_v);
	}
	if (uninf_neighbors.size() > 0)
	{
		int inf_neighbor_index = random_n(0, uninf_neighbors.size() - 1);
		Vertex informed_vertex = uninf_neighbors[inf_neighbor_index];
		HNANodeBundle message = graph.properties(informed_vertex);
		message.state_ = Two_State::informed;
		messages.insert(std::make_pair(informed_vertex, message));
		return;
	}
	else
		return;
}


std::string BroadcastSendSchemeM3::description() const
{
	return "M3";
}
