#pragma once
#include "GraphBuilder.h"
class RandomGraphBuilder : public GraphBuilder
{
	typedef adjacency_list < setS, vecS, undirectedS,
		property<vertex_properties_t, HNANodeBundle>,
		property<edge_properties_t, HNAEdgeBundle>,
		HNAGraphBundle
	> Graph;
	typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;
public:
	RandomGraphBuilder();
	~RandomGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		double p = options.p_;
		int n = options.n_vertices_;
		assert(p >= 0 && n > 0 && "ERROR: RandomgraphBuilder: nonpositive prob and/or vertices");
		boost::minstd_rand gen;
		Graph g(ERGen(gen, n, p), ERGen(), n);
		std::unique_ptr<HNAGraph> gptr(new HNAGraph());
		(*gptr).g_container = g;
		(*gptr).properties().type_ = "Random";
		return gptr;
	}
};

