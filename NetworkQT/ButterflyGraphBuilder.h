#pragma once
#include "GraphBuilder.h"
class ButterflyGraphBuilder : public GraphBuilder
{
public:
	ButterflyGraphBuilder();
	~ButterflyGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int d = options.dim_;
		assert(d > 0 && "ERROR: butterfly builder, invalid argument");

		int dpow = int(std::pow(2, d));
		int n = d * dpow;
		int s;
		int sign;
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		for (int j = 0; j < d; j++)
		{
			sign = 0;
			s = 1;
			int jpow = int(std::pow(2, j));
			for (int i = 0; i < dpow; i++)
			{
				(*gptr).AddEdge(i + j * dpow, i + (((j + 1) % d)*dpow));
				(*gptr).AddEdge(i + j * dpow, i + (((j + 1) % d) * dpow + s * jpow));
				if (sign == jpow - 1)
				{
					s *= -1;
					sign = 0;
				}
				else
					sign++;
			}
		}
		(*gptr).properties().type_ = "Butterfly";
		return gptr;
	}
};

