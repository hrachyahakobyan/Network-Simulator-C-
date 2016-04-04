#pragma once
#include "GraphBuilder.h"
#include "RandomManager.h"

class FixedRanomTreeBuilder : public GraphBuilder
{
public:
	FixedRanomTreeBuilder();
	~FixedRanomTreeBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n > 0 && "ERROR: FixedRanomTreeBuilder: nonpositive n");
		if (n == 1)
			return std::unique_ptr<HNAGraph>(new HNAGraph(1));
		else if (n == 2)
		{
			std::unique_ptr<HNAGraph> gptr(new HNAGraph(2));
			(*gptr).AddEdge(0, 1);
			return gptr;
		}
		std::vector<int> pruefer = RandomManager::sharedManager()->pruefer(n);
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		std::vector<int> degs(n, 1);
		std::vector<int>::iterator it;
		for (it = pruefer.begin(); it != pruefer.end(); ++it)
		{
			degs[*it - 1] += 1;
		}
		for (it = pruefer.begin(); it != pruefer.end(); ++it)
		{
			for (int v = 0; v < n; v++)
			{
				if (degs[v] == 1)
				{
					(*gptr).AddEdge(*it - 1, v);
					degs[*it - 1] = degs[*it - 1] - 1;
					degs[v] = degs[v] - 1;
					break;
				}
			}
		}
		int u = 0;
		int v = 0;
		for (int i = 0; i < n; i++)
		{
			if (degs[i] == 1)
			{
				if (u == 0)
					u = i;
				else
					v = i;
			}
		}
		(*gptr).AddEdge(u, v);
		return gptr;
	}
};

