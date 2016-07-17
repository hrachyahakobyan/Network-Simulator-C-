#pragma once
#include "GraphBuilder.h"
class KAryTreeBuilder : GraphBuilder
{
public:
	KAryTreeBuilder();
	~KAryTreeBuilder();

	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int height = options.height_;
		int k = options.k_;
		assert(height > 0 && "ERROR: KAryTreeBuilder: nonpositive height");
		assert(k > 0 && "ERROR: KAryTreeBuilder: nonpositive k");
		return getGraphIterative(height, k);
	}

private:

	HNAGraph getGraphRecursive(int height, int k)
	{
		HNAGraph g(1);
		if (height == 1)
		{
			for (int i = 0; i < k; i++)
				g.attach(HNAGraph(1), 0, 0);
			return g;
		}
		else
		{
			for (int i = 0; i < k; i++)
				g.attach(getGraphRecursive(height - 1, k),0,0);
			return g;
		}
	}

	std::unique_ptr<HNAGraph> getGraphIterative(int height, int k)
	{
		int lastnode = 0;

		for (int i = 1; i <= height; i++) {
			lastnode += int(std::pow(k, i));
		}
		int n = lastnode + 1;
		std::unique_ptr<HNAGraph> gptr( new HNAGraph(n));
		int parent = 0;
		for (int i = 1; i <= lastnode; i++) {
			if (i % k == 0)
				parent = i / k - 1;
			else
				parent = int(floor(i / k));
			(*gptr).add_edge(parent, i); // connect nodes with indeces parent and i
		}
		std::string type(GRAPH_KTREE);
		type.append(", height = ");
		type.append(std::to_string(height));
		type.append(", k = ");
		type.append(std::to_string(k));
		(*gptr).properties().type_ = type;
		return gptr;
	}
};

