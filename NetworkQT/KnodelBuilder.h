#pragma once
#include "HNAGraph.h"
#include "GraphBuilder.h"


class KnodelBuilder : GraphBuilder
{
public:
	KnodelBuilder()
	{}
	~KnodelBuilder()
	{}
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		assert(n > 0 && "ERROR: KnodelBuilder: n must be positive");
		if (n % 2 == 1)
			n++;
		int max_deg = int(floor(log2(n)));
		std::unique_ptr<HNAGraph>  gptr(new HNAGraph(n));
		for (int s = 1; s <= max_deg; s++)
		{
			int top = int(std::pow(2, s)) - 1;
			for (int x = 0; x <= n - 1; x++)
				for (int y = 0; y <= n - 1; y++)
				{
					if ((x + y) % n == top)
					   (*gptr).AddEdge(x, y);
				}
				
		}
		std::string type(GRAPH_KNODEL);
		(*gptr).properties().type_ = type;
		return gptr;
	}
};



