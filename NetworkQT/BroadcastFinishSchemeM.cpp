#include "stdafx.h"
#include "BroadcastFinishSchemeM.h"


BroadcastFinishSchemeM::BroadcastFinishSchemeM()
{
}


BroadcastFinishSchemeM::~BroadcastFinishSchemeM()
{
}

bool BroadcastFinishSchemeM::broadcasting_finished(const HNAGraph& graph) const
{
	vertex_range_t vr = graph.getVertices();
	for (; vr.first != vr.second; ++vr.first)
	{
		if (graph.properties(*(vr.first)).state_ == Two_State::uninformed)
			return false;
	}
	return true;
}

std::string BroadcastFinishSchemeM::description() const
{
	return "";
}
