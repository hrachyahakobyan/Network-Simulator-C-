#include "stdafx.h"
#include "BroadcastSendSchemeRadio.h"


BroadcastSendSchemeRadio::BroadcastSendSchemeRadio()
{
}


BroadcastSendSchemeRadio::~BroadcastSendSchemeRadio()
{
}

void BroadcastSendSchemeRadio::send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const
{
	messages.clear();
	if (graph.properties(node).state_ == Two_State::uninformed)
		return;
	HNAGraph::Adjacency_Range adj_v = graph.adjacent_vertices(node);
	for (; adj_v.first != adj_v.second; ++adj_v.first)
	{
		HNAGraph::Vertex cur_v = *(adj_v.first);
		HNAGraph::HNANodeBundle message = graph.properties(cur_v);
		message.state_ = Two_State::informed;
		messages.insert(std::make_pair(cur_v, message));
	}
}


std::string BroadcastSendSchemeRadio::description() const
{
	return "Radio";
}
