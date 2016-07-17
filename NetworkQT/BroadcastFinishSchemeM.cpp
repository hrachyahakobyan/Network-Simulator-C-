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
	HNAGraph::Vertex_Range vr = graph.vertices();
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
