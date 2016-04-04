#pragma once
#include "GraphBuilder.h"

class CompleteGraphBuilder : public GraphBuilder
{
public:
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n > 0 && "ERROR: CompleteGraphBuilder: nonpositive number of vertices");
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		HNAGraph::GraphContainer g = (*gptr).g_container;
		HNAGraph::Index_Map graph_indeces = get(boost::vertex_index, g);
		std::pair<HNAGraph::Vertex_Iter, HNAGraph::Vertex_Iter> vp;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first)
		{
			HNAGraph::Vertex_Iter vp2 = vp.first;
			for (; vp2 != vp.second; ++vp2)
			{
				if (graph_indeces[*vp.first] != graph_indeces[*vp2])
					(*gptr).AddEdge(*vp.first, *vp2);
			}
		}
		std::string type(GRAPH_COMPLETE);
		type.append(std::to_string(n));
		(*gptr).properties().type_ = type;
		return gptr;
	}

	CompleteGraphBuilder();
	~CompleteGraphBuilder();
};

