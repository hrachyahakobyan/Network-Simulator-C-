#pragma once
#include "GraphBuilder.h"
#include "RandomManager.h"
class RandomTreeBuilder :	public GraphBuilder
{
public:
	RandomTreeBuilder();
	~RandomTreeBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int max_children = options.children_;
		int max_height = options.height_;
		assert(max_height > 0 && max_children > 0 && "ERROR: RandomTreeBuilder: nonpositive height and/or children");
		return randomTree(max_height, max_children);
	}
private:

	std::unique_ptr<HNAGraph> randomTree(int max_height, int max_children)
	{
		std::unique_ptr<HNAGraph> tree(new HNAGraph(1));
		if (max_height == 0)
			return tree;
		int children = RandomManager::sharedManager()->random(0, max_children);
		for (int i = 0; i < children; i++)
		{
			std::unique_ptr<HNAGraph> subtree = randomTree(max_height - 1, max_children);
			(*tree).Attach(*subtree, 0, 0);
			subtree.reset();
		}
		(*tree).properties().type_ = "Random Tree";
		return tree;
	}
};

