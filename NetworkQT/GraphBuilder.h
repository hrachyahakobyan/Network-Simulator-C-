#pragma once

class GraphBuilder
{
public:
	struct GraphOptions
	{
		enum GraphType{Graph_Binomial, Graph_Bipartite, Graph_CCC, Graph_Complete, Graph_Custom, Graph_Dipper, 
					   Graph_FixedRandom, Graph_Grid, Graph_Hypercube, Graph_KTree, Graph_Knodel, Graph_Path,
					   Graph_Random, Graph_RandomTree, Graph_Torus, Graph_ScaleFreeRandom, Graph_SmallWorld};
		GraphType type_;
		int n_vertices_;
		int n_edges_;
		int dim_;
		int height_;
		int k_;
		int m_;
		int n_;
		int children_;
		int p_;
		double b_;
		std::string path_;
	};

public:
	GraphBuilder();
	virtual ~GraphBuilder();
	virtual std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options) = 0;
};

