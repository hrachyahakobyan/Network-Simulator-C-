#pragma once

#include "CompleteGraphBuilder.h"
#include "FixedRanomTreeBuilder.h"
class GraphBuilderCliqueOfTrees : public GraphBuilder
{
public:
	GraphBuilderCliqueOfTrees();
	~GraphBuilderCliqueOfTrees();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_;
		int k = options.k_;
		assert(n > 0 && k > 0 && k <= n && "ERROR: GraphBuilderCliqueOfTrees: invalid input");
		return std::unique_ptr<HNAGraph>(new HNAGraph());
	}
};

