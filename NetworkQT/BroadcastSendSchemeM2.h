#pragma once
#include "BroadcastSendScheme.h"
class BroadcastSendSchemeM2 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM2();
	~BroadcastSendSchemeM2();
	void send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const;
	std::string description() const;
};

