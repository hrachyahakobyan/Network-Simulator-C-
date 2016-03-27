#pragma once
#include "HNAGraph.h"

struct GraphOptions
{
	std::string type_;
	int n_vertices_;
	int n_edges_;
	int dim_;
	int height_;
	int k_;
};

class GraphBuilder
{
public:
	GraphBuilder();
	virtual ~GraphBuilder();
	virtual HNAGraph getGraph(const GraphOptions& options) = 0;
};

