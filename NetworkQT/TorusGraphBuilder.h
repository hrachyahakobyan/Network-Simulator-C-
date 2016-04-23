#pragma once

class TorusGraphBuilder : public GraphBuilder
{
public:
	TorusGraphBuilder();
	~TorusGraphBuilder();

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
				else
				{
					(*gptr).AddEdge(i*n, i*n + j);
				}
				if (i != m - 1)
				{
					(*gptr).AddEdge(i*n + j, (i + 1)*n + j);
				}
				else
				{
					(*gptr).AddEdge(j, i*n + j);
				}
			}
		}

		(*gptr).properties().type_ = "Torus";
		return gptr;
	}
};

