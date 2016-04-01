#pragma once
#include "GraphBuilder.h"
class CCCGraphBuilder : public GraphBuilder
{
	typedef adjacency_list < setS, vecS, undirectedS,
		property<vertex_properties_t, HNANodeBundle>,
		property<edge_properties_t, HNAEdgeBundle>,
		HNAGraphBundle
	> Graph;
public:
	CCCGraphBuilder();
	~CCCGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int dim = options.dim_;
		assert(dim > 0 && "ERROR: CCCGraphBuilder: nonpositive dim");
		int size = int(std::pow(2, dim));
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(size*dim));
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				int x0 = i;
				int y0 = j;
				int x1 = i;
				int y1 = mod(j + 1, dim);
				int x2 = i;
				int y2 = mod(j - 1, dim);
				int x3 = i ^ int(std::pow(2, j));
				int y3 = j;
				(*gptr).AddEdge(x0*dim + y0, x1*dim + y1);
				(*gptr).AddEdge(x0*dim + y0, x2*dim + y2);
				(*gptr).AddEdge(x0*dim + y0, x3*dim + y3);
			}
		}
		(*gptr).properties().type_ = "CCC";
		return gptr;
	}
private:
	int mod(int a, int n)
	{ 
		return (a % n) + (a < 0 ? n : 0);
	}

};

