#pragma once
#include "HNAGraph.h"

class BroadcastSendScheme
{
public:
	BroadcastSendScheme();
	virtual ~BroadcastSendScheme();
	virtual void send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const = 0;
	virtual std::string description() const = 0;
};

