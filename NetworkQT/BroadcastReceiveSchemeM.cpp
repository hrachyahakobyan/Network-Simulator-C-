#include "stdafx.h"
#include "BroadcastReceiveSchemeM.h"


BroadcastReceiveSchemeM::BroadcastReceiveSchemeM()
{
}


BroadcastReceiveSchemeM::~BroadcastReceiveSchemeM()
{
}

void BroadcastReceiveSchemeM::receive(const HNAGraph& graph, const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages, HNAGraph::HNANodeBundle& message) const
{
	message = graph.properties(node);
	message.informers_.clear();
	typedef std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>::const_iterator map_it;
	map_it it;
	for (it = messages.begin(); it != messages.end(); ++it)
	{
		const HNAGraph::HNANodeBundle* m = &((*it).second);
		assert(m->state_ > -1 && "ERROR: BroadcastReceiveSchemeM1: vertex has negative state");
		if (m->state_ == Two_State::informed)
		{
			message.state_ = Two_State::informed;
			message.informers_.insert((*it).first);
		}
	}
}

std::string BroadcastReceiveSchemeM::description() const
{
	return "M";
}