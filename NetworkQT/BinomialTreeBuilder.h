#pragma once
#include "GraphBuilder.h"

class BinomialTreeBuilder : GraphBuilder
{
	typedef adjacency_list < setS, vecS, undirectedS,
		property<vertex_properties_t, HNANodeBundle>,
		property<edge_properties_t, HNAEdgeBundle>,
		HNAGraphBundle
	> Graph;
	typedef  graph_traits<Graph>::vertex_descriptor Vertex;
	typedef  property_map<Graph, vertex_index_t>::type IndexMap;
	typedef  graph_traits<Graph>::vertex_iterator vertex_iter;

public:
	BinomialTreeBuilder();
	~BinomialTreeBuilder();

public:
	HNAGraph getGraph(const GraphOptions& options)
	{
		int height = options.height_;
		assert(height > 0 && "ERROR: BinomialTreeBuilder: non-positive hight \n");
		HNAGraph g(1);
		if (height == 1)
		{
			return g;
		}
		for (int i = 1; i <= height; i++)
		{
			HNAGraph g2 = HNAGraph(g);
			g.Attach(g2, 0, 0);
		}
		std::string type(GRAPH_BINOMIAL);
		type.append(", height = ");
		type.append(std::to_string(height));
		g.properties().type_ = type;
		return g;
	}
};

