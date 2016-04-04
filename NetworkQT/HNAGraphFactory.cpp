#include "stdafx.h"
#include "HNAGraphFactory.h"
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

HNAGraphFactory *HNAGraphFactory::graphFactory = 0;

HNAGraphFactory::HNAGraphFactory()
{
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Complete, std::unique_ptr<GraphBuilder>(new CompleteGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Knodel, std::unique_ptr<GraphBuilder>(new KnodelBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_KTree, std::unique_ptr<GraphBuilder>(new KAryTreeBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Binomial, std::unique_ptr<GraphBuilder>(new BinomialTreeBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Hypercube, std::unique_ptr<GraphBuilder>(new HypercubeBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Grid, std::unique_ptr<GraphBuilder>(new GridGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Torus, std::unique_ptr<GraphBuilder>(new TorusGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Random, std::unique_ptr<GraphBuilder>(new RandomGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_CCC, std::unique_ptr<GraphBuilder>(new CCCGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Bipartite, std::unique_ptr<GraphBuilder>(new BipartiteGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_Dipper, std::unique_ptr<GraphBuilder>(new DipperGraphBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_RandomTree, std::unique_ptr<GraphBuilder>(new RandomTreeBuilder)));
	builders_.insert(std::make_pair(GraphBuilder::GraphOptions::GraphType::Graph_FixedRandom, std::unique_ptr<GraphBuilder>(new FixedRanomTreeBuilder)));
}


HNAGraphFactory::~HNAGraphFactory()
{
	std::map<GraphBuilder::GraphOptions::GraphType, std::unique_ptr<GraphBuilder>>::iterator it;
	for (it = builders_.begin(); it != builders_.end(); ++it)
	{
		(*it).second.reset();
	}
	builders_.clear();
}

std::unique_ptr<HNAGraph> HNAGraphFactory::getGraph(const GraphBuilder::GraphOptions& options)
{
	assert(builders_.find(options.type_) != builders_.end() && "ERROR: HNAGraphFactory: nonexistent graph type");
	std::unique_ptr<GraphBuilder>* blder = &(*(builders_.find(options.type_))).second;
	std::unique_ptr<HNAGraph>gptr = (*(*blder)).getGraph(options);
	return gptr;
}
