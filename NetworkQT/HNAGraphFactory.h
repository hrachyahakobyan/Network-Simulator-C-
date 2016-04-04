#pragma once
#include "GraphBuilder.h"
class HNAGraphFactory
{
public:
	static HNAGraphFactory* sharedFactory()
	{
		if (graphFactory == 0)
		{
			graphFactory = new HNAGraphFactory();
		}
		return graphFactory;
	}
	static void release()
	{
		if (graphFactory != 0)
		{
			delete graphFactory;
			graphFactory = 0;
		}
	}

	std::unique_ptr<HNAGraph> getGraph(const GraphBuilder::GraphOptions& options);

private:
	static HNAGraphFactory* graphFactory;
	HNAGraphFactory();
	~HNAGraphFactory();
	std::map<std::string, std::unique_ptr<GraphBuilder>> builders_;
};

