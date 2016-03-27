#pragma once
#include "HNAGraph.h"
class BroadcastFinishScheme
{
public:
	BroadcastFinishScheme();
	virtual ~BroadcastFinishScheme();
	virtual bool broadcasting_finished(const HNAGraph& graph) const = 0;
	virtual std::string description() const = 0;
};

