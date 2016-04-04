#pragma once
#include "BroadcastSendScheme.h"
class BroadcastSendSchemeM3 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM3();
	~BroadcastSendSchemeM3();
	void send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const;
	std::string description() const;
};

