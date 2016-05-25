#include "stdafx.h"
#include "GraphBuilder.h"
typedef GraphBuilder::GraphOptions::GraphType GT;
const std::map<GT, std::string> GraphBuilder::GraphOptions::typeMap_ = 
{
	{ GT::Graph_Binomial, "Binomial Tree" },
	{ GT::Graph_Bipartite, "Bipartite graph" },
	{ GT::Graph_CCC, "Cube connected cycle" },
	{ GT::Graph_Random, "Erdos-Reniy random graph" },
	{ GT::Graph_Complete, "Complete graph" },
	{ GT::Graph_DeBruin, "De Brujin" },
	{ GT::Graph_Dipper, "Dipper" },
	{ GT::Graph_FixedRandom, "Fixed random tree" },
	{ GT::Graph_Grid, "Grid" },
	{ GT::Graph_Hypercube, "Hypercube" }
};

GraphBuilder::GraphBuilder()
{
}


GraphBuilder::~GraphBuilder()
{
}
