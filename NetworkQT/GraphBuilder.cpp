#include "stdafx.h"
#include "GraphBuilder.h"
typedef GraphBuilder::GraphOptions::GraphType GT;
const std::map<GT, std::string> GraphBuilder::GraphOptions::typeMap_ = 
{
	{ GT::Graph_Binomial, "Binomial Tree" },
	{ GT::Graph_Bipartite, "Bipartite graph" },
	{ GT::Graph_CCC, "Cube connected cycle" },
	{ GT::Graph_Random, "Erdos-Reniy random graph" },
	{ GT::Graph_Complete, "Complete graph" }
};

GraphBuilder::GraphBuilder()
{
}


GraphBuilder::~GraphBuilder()
{
}
