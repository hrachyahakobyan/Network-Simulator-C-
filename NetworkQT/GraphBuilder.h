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
	int m_;
	int n_;
	double p_;
};

class GraphBuilder
{
public:
	GraphBuilder();
	virtual ~GraphBuilder();
	virtual std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options) = 0;
};

