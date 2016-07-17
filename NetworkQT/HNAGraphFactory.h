#pragma once
#include "BinomialTreeBuilder.h"
#include "CompleteGraphBuilder.h"
#include "KnodelBuilder.h"
#include "KAryTreeBuilder.h"
#include "HypercubeBuilder.h"
#include "GridGraphBuilder.h"
#include "TorusGraphBuilder.h"
#include "RandomGraphBuilder.h"
#include "CCGraphBuilder.h"
#include "BipartiteGraphBuilder.h"
#include "DipperGraphBuilder.h"
#include "RandomTreeBuilder.h"
#include "FixedRanomTreeBuilder.h"
#include "ScaleFreeRandomGraphBuilder.h"
#include "SmallWorldGraphBuilder.h"
#include "ButterflyGraphBuilder.h"
#include "ShuffleExchangeBuilder.h"
#include "DeBruinBuilder.h"

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
	std::map<GraphBuilder::GraphOptions::GraphType, std::unique_ptr<GraphBuilder>> builders_;
};

