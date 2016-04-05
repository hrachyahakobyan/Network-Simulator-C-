#include "stdafx.h"
#include "HNAGraphWriter.h"
#include "FileManager.h"

std::unique_ptr<HNAGraphWriter> HNAGraphWriter::defaultWrtier()
{
	std::unique_ptr<HNAGraphWriter> ptr(new HNAGraphWriter(HNAVertexWriter::defaultWriter(), HNAEdgeWriter::defaultWriter(), HNAGraphPropertyWriter::defaultWriter()));
	return ptr;
}

boost::filesystem::path HNAGraphWriter::writeGraph(const HNAGraph& graph, const boost::filesystem::path& path, const std::string& name) 
{
	v_.set_deg_map(graph.deg_map());
	v_.set_v_prop(graph.v_params());
	g_.set_g_prop(graph.properties());
	g_.edges() = graph.getEdgeCount();
	g_.vertices() = graph.getVertexCount();
	std::string p(path.string());
	assert(boost::filesystem::exists(p) && "ERROR: HNAGraphWriter: path does not exist ");
	p.append("/");
	p.append(name);
	p.append(".dot");
	if (FileManager::sharedManager()->file_exists(p))
		FileManager::sharedManager()->del_file(p);
	std::ofstream of(p.c_str());
	boost::write_graphviz(of, graph.g_container, v_, e_, g_);
	return p;
}
