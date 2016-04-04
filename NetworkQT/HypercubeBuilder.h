#pragma once
#include "HNAGraph.h"
#include "GraphBuilder.h"

class HypercubeBuilder : public GraphBuilder
{
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
		HNAGraph::GraphContainer g = (*gptr).g_container;
		HNAGraph::Index_Map graph_indeces = get(boost::vertex_index, g);
		std::pair<HNAGraph::Vertex_Iter, HNAGraph::Vertex_Iter> vp;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first)
		{
			HNAGraph::Vertex v = *vp.first;
			int v_index = graph_indeces[v];
			std::vector<int> neighbor_indices(dims, v_index);
			for (int i = 0; i < dims; i++)
			{
				neighbor_indices[i] ^= 1 << i;
			}
	
			std::pair<HNAGraph::Vertex_Iter, HNAGraph::Vertex_Iter> vp2;
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


