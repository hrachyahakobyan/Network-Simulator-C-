#pragma once

class RandomGraphBuilder : public GraphBuilder
{
	typedef boost::erdos_renyi_iterator<boost::minstd_rand, HNAGraph::GraphContainer> ERGen;
public:
	RandomGraphBuilder();
	~RandomGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int p = options.p_;
		int n = options.n_vertices_;
		assert(p >= 0 && n > 0 && p <= 100 && "ERROR: RandomgraphBuilder: nonpositive prob and/or vertices");
		if (n == 1)
			return std::unique_ptr<HNAGraph>(new HNAGraph(1));
		boost::minstd_rand gen;
		std::cout << double(p) / 100;
		HNAGraph::GraphContainer g(ERGen(gen, n, double(p)/100), ERGen(), n);
		std::unique_ptr<HNAGraph> gptr(new HNAGraph());
		(*gptr).g_container = g;
		(*gptr).properties().type_ = "Random";
		return std::move(gptr);
	}
};

