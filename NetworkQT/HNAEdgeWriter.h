#pragma once
#include <fstream>

struct HNAEdgeWriterOptions
{
	static HNAEdgeWriterOptions defaultOptions()
	{
		return HNAEdgeWriterOptions();
	}
};


class HNAEdgeWriter
{
public:
	HNAEdgeWriter(const HNAEdgeWriterOptions& op) : op_(op) {};
	~HNAEdgeWriter();
	
	static HNAEdgeWriter defaultWriter()
	{
		return HNAEdgeWriter(HNAEdgeWriterOptions::defaultOptions());
	}

	void operator()(std::ostream &out, const HNAGraph::Edge& e) const
	{

	}
private:
	HNAEdgeWriterOptions op_;
};

