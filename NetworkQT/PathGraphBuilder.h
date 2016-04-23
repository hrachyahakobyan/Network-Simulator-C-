#pragma once

class PathGraphBuilder : public GraphBuilder
{
public:
	PathGraphBuilder();
	~PathGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n > 0 && "ERROR: PathGraphBuilder: nonpositive vertices");
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		for (int i = 0; i < n - 1; i++)
			(*gptr).AddEdge(i, i + 1);
		return gptr;
	}
};

