#pragma once
#include "HNAGraph.h"
#include "GraphBuilder.h"

using namespace boost;

class KnodelBuilder : GraphBuilder
{
	typedef adjacency_list<setS, vecS, undirectedS,
		property<vertex_properties_t, HNANodeBundle>,
		property<edge_properties_t, HNAEdgeBundle>,
		HNAGraphBundle
	> Graph;
	typedef  graph_traits<Graph>::vertex_descriptor Vertex;
	typedef  property_map<Graph, vertex_index_t>::type IndexMap;
	typedef  graph_traits<Graph>::vertex_iterator vertex_iter;
public:
	KnodelBuilder()
	{}
	~KnodelBuilder()
	{}
	HNAGraph getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n % 2 == 1 && "ERROR: KnodelBuilder: n must be even");
		int max_deg = int(floor(log2(n)));
		HNAGraph graph(n);
		for (int s = 1; s <= max_deg; s++)
		{
			int top = int(std::pow(2, s)) - 1;
			for (int x = 0; x <= n - 1; x++)
				for (int y = 0; y <= n - 1; y++)
				{
					if ((x + y) % n == top)
					   graph.AddEdge(x, y);
				}
				
		}
		std::string type(GRAPH_KNODEL);
		graph.properties().type_ = type;
		return graph;
	}
};



