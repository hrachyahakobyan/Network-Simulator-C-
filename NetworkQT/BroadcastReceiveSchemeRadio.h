#pragma once
#include "BroadcastReceiveScheme.h"
class BroadcastReceiveSchemeRadio :	public BroadcastReceiveScheme
{
public:
	BroadcastReceiveSchemeRadio();
	~BroadcastReceiveSchemeRadio();
	void receive(const HNAGraph& graph, const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages, HNAGraph::HNANodeBundle& message) const;
	std::string description() const;
};

