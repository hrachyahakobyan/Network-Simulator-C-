#pragma once
#include "GraphBuilder.h"

using namespace boost;

class CompleteGraphBuilder : public GraphBuilder
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
	HNAGraph getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n > 0 && "ERROR: CompleteGraphBuilder: nonpositive number of vertices");
		HNAGraph graph(n);
		Graph g = graph.g_container;
		IndexMap graph_indeces = get(vertex_index, g);
		std::pair<vertex_iter, vertex_iter> vp;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first)
		{
			vertex_iter vp2 = vp.first;
			for (; vp2 != vp.second; ++vp2)
			{
				if (graph_indeces[*vp.first] != graph_indeces[*vp2])
					graph.AddEdge(*vp.first, *vp2);
			}
		}
		std::string type(GRAPH_COMPLETE);
		type.append(std::to_string(n));
		graph.properties().type_ = type;
		return graph;
	}

	CompleteGraphBuilder();
	~CompleteGraphBuilder();
};

