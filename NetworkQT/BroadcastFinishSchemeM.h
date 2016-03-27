#pragma once
#include "BroadcastFinishScheme.h"
class BroadcastFinishSchemeM :
	public BroadcastFinishScheme
{
public:
	BroadcastFinishSchemeM();
	~BroadcastFinishSchemeM();
	bool broadcasting_finished(const HNAGraph& graph) const;
	std::string description() const;
};

