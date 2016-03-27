#pragma once
#include "BroadcastReceiveScheme.h"


class BroadcastReceiveSchemeM : public BroadcastReceiveScheme
{
public:
	BroadcastReceiveSchemeM();
	~BroadcastReceiveSchemeM();
	void receive(const HNAGraph& graph, const Vertex& node, const std::map<Vertex, HNANodeBundle>& messages, HNANodeBundle& message) const;
	std::string description() const;
};

