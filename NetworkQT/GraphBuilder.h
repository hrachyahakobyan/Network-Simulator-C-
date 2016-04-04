#pragma once
#include "HNAGraph.h"

class GraphBuilder
{
public:
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
		int children_;
		double p_;
		std::string path_;
	};
public:
	GraphBuilder();
	virtual ~GraphBuilder();
	virtual std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options) = 0;
};

