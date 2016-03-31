#pragma once
#include "HNAGraph.h"
#include "GraphBuilder.h"

using namespace boost;

class HypercubeBuilder : public GraphBuilder
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
	HypercubeBuilder()
	{}
	~HypercubeBuilder()
	{}
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int dims = options.dim_;
		assert(dims > 0 && "Error: HypercubeBuilder: nonpositive dimensions");
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(int(std::pow(2, dims))));
		Graph g = (*gptr).g_container;
		IndexMap graph_indeces = get(vertex_index, g);
		std::pair<vertex_iter, vertex_iter> vp;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first)
		{
			Vertex v = *vp.first;
			int v_index = graph_indeces[v];
			std::vector<int> neighbor_indices(dims, v_index);
			for (int i = 0; i < dims; i++)
			{
				neighbor_indices[i] ^= 1 << i;
			}
	
			std::pair<vertex_iter, vertex_iter> vp2;
			for (vp2 = vertices(g); vp2.first != vp2.second; ++vp2.first)
			{
				std::vector<int>::iterator it;
				for (it = neighbor_indices.begin(); it != neighbor_indices.end(); ++it)
				{
					if (graph_indeces[*vp2.first] == *it)
					{
						(*gptr).AddEdge(v, *vp2.first);
						break;
					}
				}
			}

		}
		std::string type(GRAPH_HYPER);
		type.append(", dim = ");
		type.append(std::to_string(dims));
		(*gptr).properties().type_ = type;
		return gptr;
	}
private:
	std::string dec_to_string(int number)
	{
		if (number == 0) return "0";
		if (number == 1) return "1";

		if (number % 2 == 0)
			return dec_to_string(number / 2) + "0";
		else
			return dec_to_string(number / 2) + "1";
	}

	int string_to_dec(std::string number)
	{
		int result = 0, pow = 1;
		for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
			result += (number[i] - '0') * pow;

		return result;
	}
};


