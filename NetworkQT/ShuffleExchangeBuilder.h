#pragma once
#include "GraphBuilder.h"
class ShuffleExchangeBuilder : public GraphBuilder
{
public:
	ShuffleExchangeBuilder();
	~ShuffleExchangeBuilder();

	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int d = options.dim_;
		assert(d > 0 && "ERROR: butterfly builder, invalid argument");

		int dpow = int(std::pow(2, d));
		int n = dpow;
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		(*gptr).AddEdge(0, 1);
		for (int i = 1; i < dpow - 1; i++)
		{
			if (i % 2 == 0)
				(*gptr).AddEdge(i, i + 1);
			(*gptr).AddEdge(i, (i * 2) % (dpow - 1));
		}
		(*gptr).properties().type_ = "Shuffle exchange";
		return gptr;
	}
};

