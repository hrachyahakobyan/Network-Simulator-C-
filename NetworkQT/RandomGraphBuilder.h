#pragma once
#include "GraphBuilder.h"
class RandomGraphBuilder : public GraphBuilder
{
	typedef boost::erdos_renyi_iterator<boost::minstd_rand, HNAGraph::GraphContainer> ERGen;
public:
	RandomGraphBuilder();
	~RandomGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		double p = options.p_;
		int n = options.n_vertices_;
		assert(p >= 0 && n > 0 && "ERROR: RandomgraphBuilder: nonpositive prob and/or vertices");
		boost::minstd_rand gen;
		HNAGraph::GraphContainer g(ERGen(gen, n, p), ERGen(), n);
		std::unique_ptr<HNAGraph> gptr(new HNAGraph());
		(*gptr).g_container = g;
		(*gptr).properties().type_ = "Random";
		return gptr;
	}
};

