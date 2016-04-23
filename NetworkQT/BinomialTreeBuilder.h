#pragma once

class BinomialTreeBuilder : GraphBuilder
{
public:
	BinomialTreeBuilder();
	~BinomialTreeBuilder();
public:
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int height = options.height_;
		assert(height > 0 && "ERROR: BinomialTreeBuilder: non-positive hight \n");
		std::unique_ptr<HNAGraph> gpt(new HNAGraph(1));
		if (height == 1)
		{
			return gpt;
		}
		for (int i = 1; i <= height; i++)
		{
			HNAGraph g2 = HNAGraph(*gpt);
			(*gpt).Attach(g2, 0, 0);
		}
		std::string type = GRAPH_BINOMIAL;
		type.append(", height = ");
		type.append(std::to_string(height));
		(*gpt).properties().type_ = type;
		return gpt;
	}
};

