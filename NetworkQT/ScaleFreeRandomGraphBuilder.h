#pragma once

#include "FixedRanomTreeBuilder.h"
#include "RandomManager.h"
class ScaleFreeRandomGraphBuilder : public GraphBuilder
{
public:
	ScaleFreeRandomGraphBuilder();
	~ScaleFreeRandomGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		// the number of new vertices to be added
		int n = options.n_;
		// the number of existing vertices
		int m = options.m_;
		// number of edges for each new vertex
		int k = options.k_;
		assert(n > 0 && m > 0 && k > 0 && "ERROR:ScaleFreeRandomGraphBuilder: invalid parameters");
		FixedRanomTreeBuilder tb;
		GraphBuilder::GraphOptions op;
		op.n_vertices_ = m;
		std::unique_ptr<HNAGraph> gptr = tb.getGraph(op);
		RandomManager* rand = RandomManager::sharedManager();
		for (HNAGraph::Vertex v = m; v < n + m; v++)
		{
			(*gptr).add_vertex();
			std::set<HNAGraph::Vertex> vp = (*gptr).vertices_set();
			for (int l = 0; l < k; l++)
			{
				std::vector<double> probs;
				std::vector<HNAGraph::Vertex> vs;
				std::set<HNAGraph::Vertex>::iterator vpit;
				int sum = 0;
				for (vpit = vp.begin(); vpit != vp.end(); ++vpit)
				{
					if (*vpit != v)
						sum += (*gptr).vertex_degree(*vpit);
				}
				for (vpit = vp.begin(); vpit != vp.end(); ++vpit)
				{
					if (v != *vpit)
					{
						int deg = (*gptr).vertex_degree(*vpit);
						double p = sum == 0 ? 1 : double(deg) / sum;
						probs.push_back(p);
						vs.push_back(*vpit);
						if (sum == 0)
							break;
					}
				}
				int index = rand->random_index(probs);
				vp.erase(vs[index]);
				(*gptr).add_edge(vs[index], v);
			}
		}
		std::string type("Scale Free Random Graph");
		type.append("Kernel = "); type.append(std::to_string(m));
		type.append("/n New vertices "); type.append(std::to_string(n));
		type.append("/n Edges "); type.append(std::to_string(k));
		return gptr;
	}
};

