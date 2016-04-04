#pragma once
#include "BroadcastSendScheme.h"
class BroadcastSendSchemeM2 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM2();
	~BroadcastSendSchemeM2();
	void send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const;
	std::string description() const;
};

