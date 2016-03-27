#pragma once
#include "HNAGraphPropertyWriter.h"
#include "HNAEdgeWriter.h"
#include "HNAVertexWriter.h"
#include <boost/filesystem.hpp>
#include <boost/graph/graphviz.hpp>


class HNAGraphWriter
{
	typedef boost::filesystem::path Path;
public:
	HNAGraphWriter(const HNAGraphPropertyWriterOptions& g_op, const HNAVertexWriteOptions& v_op, const HNAEdgeWriterOptions& e_op) : g_(g_op), v_(v_op), e_(e_op){};
	HNAGraphWriter(const HNAVertexWriter& v, const HNAEdgeWriter& e, const HNAGraphPropertyWriter& g) : v_(v), e_(e), g_(g){};
	~HNAGraphWriter(){};
	Path writeGraph(const HNAGraph& graph, const Path& path, const std::string& name);
private:
	HNAGraphPropertyWriter g_;
	HNAVertexWriter v_;
	HNAEdgeWriter e_;
};

