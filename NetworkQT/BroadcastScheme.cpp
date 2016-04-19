#include "stdafx.h"
#include "BroadcastScheme.h"


void BroadcastScheme::send(const HNAGraph& graph, const HNAGraph::Vertex& node, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) const
{
	(*s_).send(graph, node, messages);
}

void BroadcastScheme::receive(const HNAGraph& graph, const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages, HNAGraph::HNANodeBundle& message) const
{
	(*r_).receive(graph, node, messages, message);
}

bool BroadcastScheme::broadcasting_finished(const HNAGraph& graph) const
{
	return (*f_).broadcasting_finished(graph);
}

std::string BroadcastScheme::description() const
{
	std::string desc;
	desc.append("Sending Scheme = ");
	desc.append((*s_).description());
	desc.append(", Receiving Scheme = ");
	desc.append((*r_).description());
	return desc;
}