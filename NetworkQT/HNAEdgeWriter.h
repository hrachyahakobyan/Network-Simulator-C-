#pragma once
#include <fstream>
#include "HNAGraph.h"

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

    void operator()(std::ostream &out, const Edge& e) const
	{

	}
private:
	HNAEdgeWriterOptions op_;
};

