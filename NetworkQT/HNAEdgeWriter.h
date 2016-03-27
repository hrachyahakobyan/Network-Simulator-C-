#pragma once
#include <fstream>
#include "HNAGraph.h"

struct HNAEdgeWriterOptions
{

};


class HNAEdgeWriter
{
public:
	HNAEdgeWriter(const HNAEdgeWriterOptions& op) : op_(op) {};
	~HNAEdgeWriter();
    void operator()(std::ostream &out, const Edge& e) const
	{

	}
private:
	HNAEdgeWriterOptions op_;
};

