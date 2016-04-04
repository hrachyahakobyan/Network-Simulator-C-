#pragma once
#include "GraphBuilder.h"
#include "CompleteGraphBuilder.h"
#include "DipperGraphBuilder.h"
#include "PathGraphBuilder.h"

class DipperGraphBuilder : public GraphBuilder
{
public:
	DipperGraphBuilder();
	~DipperGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_;
		int m = options.m_;
		assert(n > 0 && m > 0 && "ERROR: DipperGraphBuilder: nonpositive n and/or m");
		GraphOptions compOptions;
		compOptions.n_vertices_ = m;
		GraphOptions pathOptions;
		pathOptions.n_vertices_ = n;
		CompleteGraphBuilder bldc;
		PathGraphBuilder bldp;
		std::unique_ptr<HNAGraph> gptrc = bldc.getGraph(compOptions);
		std::unique_ptr<HNAGraph> gptrp = bldp.getGraph(pathOptions);
		(*gptrc).Attach(*gptrp, 0, 0);
		gptrp.reset();
		(*gptrc).properties().type_ = "Dipper";
		return gptrc;
	}
};

