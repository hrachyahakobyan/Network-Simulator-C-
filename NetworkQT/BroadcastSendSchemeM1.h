#pragma once
#include "BroadcastSendScheme.h"

class BroadcastSendSchemeM1 : public BroadcastSendScheme
{
public:
	BroadcastSendSchemeM1();
	~BroadcastSendSchemeM1();
	void send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const;
	std::string description() const;
};

