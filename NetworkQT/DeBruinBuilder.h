#pragma once
#include "GraphBuilder.h"
class DeBruinBuilder : public GraphBuilder
{
public:
	DeBruinBuilder();
	~DeBruinBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int d = options.dim_;
		assert(d > 0 && "ERROR: Debruin builder, invalid argument");

		int dpow = int(std::pow(2, d));
		int n = dpow;
		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		for (int i = 0; i < dpow; i++)
		{
			(*gptr).add_edge(i, (2 * i) % dpow);
			(*gptr).add_edge(i, (2 * i) % dpow + 1);
		}
		(*gptr).properties().type_ = "DeBruin";
		return gptr;
	}
};

