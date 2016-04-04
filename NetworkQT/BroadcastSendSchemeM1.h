#pragma once
#include "BroadcastSendScheme.h"

class BroadcastSendSchemeM1 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM1();
	~BroadcastSendSchemeM1();
	void send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const;
	std::string description() const;
};

