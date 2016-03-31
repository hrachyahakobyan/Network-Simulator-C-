#include "stdafx.h"
#include "HNAGraphFactory.h"

HNAGraphFactory *HNAGraphFactory::graphFactory = 0;

HNAGraphFactory::HNAGraphFactory()
{
	builders_.insert(std::make_pair(GRAPH_COMPLETE, std::unique_ptr<GraphBuilder>(new CompleteGraphBuilder)));
	builders_.insert(std::make_pair(GRAPH_KNODEL, std::unique_ptr<GraphBuilder>(new KnodelBuilder)));
	builders_.insert(std::make_pair(GRAPH_KTREE, std::unique_ptr<GraphBuilder>(new KAryTreeBuilder)));
	builders_.insert(std::make_pair(GRAPH_BINOMIAL, std::unique_ptr<GraphBuilder>(new BinomialTreeBuilder)));
	builders_.insert(std::make_pair(GRAPH_HYPER, std::unique_ptr<GraphBuilder>(new HypercubeBuilder)));
}


HNAGraphFactory::~HNAGraphFactory()
{
	std::map<std::string, std::unique_ptr<GraphBuilder>>::iterator it;
	for (it = builders_.begin(); it != builders_.end(); ++it)
	{
		(*it).second.reset();
	}
	builders_.clear();
}

std::unique_ptr<HNAGraph> HNAGraphFactory::getGraph(const GraphOptions& options)
{
	assert(builders_.find(options.type_.c_str()) != builders_.end() && "ERROR: HNAGraphFactory: nonexistent graph type");
	std::unique_ptr<GraphBuilder>* blder = &(*(builders_.find(options.type_.c_str()))).second;
	std::unique_ptr<HNAGraph>gptr = (*(*blder)).getGraph(options);
	return gptr;
}
