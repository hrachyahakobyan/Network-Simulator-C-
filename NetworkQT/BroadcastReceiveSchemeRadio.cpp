#include "stdafx.h"
#include "BroadcastReceiveSchemeRadio.h"


BroadcastReceiveSchemeRadio::BroadcastReceiveSchemeRadio()
{
}


BroadcastReceiveSchemeRadio::~BroadcastReceiveSchemeRadio()
{
}


void BroadcastReceiveSchemeRadio::receive(const HNAGraph& graph, const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages, HNAGraph::HNANodeBundle& message) const
{
	message = graph.properties(node);
	if (message.state_ == Two_State::informed)
		return;
	typedef std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>::const_iterator map_it;
	map_it it;
	int informed_count = 0;
	for (it = messages.begin(); it != messages.end(); ++it)
	{
		const HNAGraph::HNANodeBundle* m = &((*it).second);
		assert(m->state_ > -1 && "ERROR: BroadcastReceiveSchemeRadio: vertex has negative state");
		if (m->state_ == Two_State::informed)
		{
			informed_count++;
			message.state_ = Two_State::informed;
		}
		if (informed_count == 2)
		{
			message.state_ = Two_State::uninformed;
			break;
		}
	}
}

std::string BroadcastReceiveSchemeRadio::description() const
{
	return "Radio";
}