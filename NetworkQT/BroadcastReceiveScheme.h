#pragma once

class BroadcastReceiveScheme
{
public:
	BroadcastReceiveScheme();
	virtual ~BroadcastReceiveScheme();
	virtual void receive(const HNAGraph& graph, const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages, HNAGraph::HNANodeBundle& message) const = 0;
	virtual std::string description() const = 0;
};

