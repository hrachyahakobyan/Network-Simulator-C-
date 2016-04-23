#pragma once

class CustomGraphBuilder : public GraphBuilder
{
public:
	CustomGraphBuilder();
	~CustomGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		std::unique_ptr<HNAGraph> gptr(new HNAGraph());
		//std::istringstream str("../data/g.dot");
		//boost::read_graphviz(str, (*gptr).g_container, boost::dynamic_properties());
		return gptr;
	}
};

