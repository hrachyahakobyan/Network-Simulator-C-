#pragma once

class BipartiteGraphBuilder : public GraphBuilder
{
public:
	BipartiteGraphBuilder();
	~BipartiteGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_;
		int m = options.m_;
		assert(n > 0 && m > 0 && "ERROR:Bipartite Graph Builder: non positive n and/or m");
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n + m));
		for (int i = 0; i < n; i++)
		{
			for (int j = n; j < n + m; j++)
			{
				(*gptr).AddEdge(i, j);
			}
		}
		(*gptr).properties().type_ = "Bipartite";
		return gptr;
	}
};

