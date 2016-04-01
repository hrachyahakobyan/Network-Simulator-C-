#pragma once
#include "GraphBuilder.h"
class GridGraphBuilder : public GraphBuilder
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
	GridGraphBuilder();
	~GridGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_;
		int m = options.m_;
		assert(n > 0 && m > 0 && "Error: GridGraphBuilder: nonpositive n and/or m");
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n*m));
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != n - 1)
				{
					(*gptr).AddEdge(i*n + j, i*n + j + 1);
				}
				if (i != m - 1)
				{
					(*gptr).AddEdge(i*n + j, (i + 1)*n + j);
				}
			}
		}
		(*gptr).properties().type_ = "Grid";
		return gptr;
	}
};

