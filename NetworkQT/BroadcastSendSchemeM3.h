#pragma once
#include "BroadcastSendScheme.h"
class BroadcastSendSchemeM3 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM3();
	~BroadcastSendSchemeM3();
	void send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const;
	std::string description() const;
};

