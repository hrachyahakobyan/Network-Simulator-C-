#pragma once
#include "HNAGraph.h"


class BroadcastReceiveScheme
{
public:
	BroadcastReceiveScheme();
	virtual ~BroadcastReceiveScheme();
	virtual void receive(const HNAGraph& graph, const Vertex& node, const std::map<Vertex, HNANodeBundle>& messages, HNANodeBundle& message) const = 0;
	virtual std::string description() const = 0;
};

