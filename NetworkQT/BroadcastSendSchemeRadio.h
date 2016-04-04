#pragma once
#include "BroadcastSendScheme.h"
class BroadcastSendSchemeRadio : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeRadio();
	~BroadcastSendSchemeRadio();
	void send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const;
	std::string description() const;
};

