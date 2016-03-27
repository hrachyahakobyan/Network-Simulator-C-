#include "stdafx.h"
#include "HNAGraphWriter.h"



boost::filesystem::path HNAGraphWriter::writeGraph(const HNAGraph& graph, const Path& path, const std::string& name) 
{
	v_.set_v_prop(graph.v_params());
	g_.set_g_prop(graph.properties());
	g_.edges() = graph.getEdgeCount();
	g_.vertices() = graph.getVertexCount();
	std::string p(path.string());
	assert(boost::filesystem::exists(p) && "ERROR: HNAGraphWriter: path does not exist ");
	p.append("/");
	p.append(name);
	p.append(".dot");
	assert(!boost::filesystem::exists(p) && "ERROR: HNAGraphWriter: file already exists ");
	std::ofstream of(p.c_str());
	boost::write_graphviz(of, graph.g_container, v_, e_, g_);
	return p;
}
