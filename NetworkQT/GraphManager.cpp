#include "stdafx.h"
#include "GraphManager.h"
GraphManager* GraphManager::_graphManager = 0;

GraphManager::GraphManager() : rend_ptr_(new CMDGraphRenderer())
{
	HNAGraphPropertyWriterOptions gop(true, true, true, false, false);
	HNAVertexWriteOptions vop(false, false);
	HNAEdgeWriterOptions eop;
	writer_ptr_.reset(new HNAGraphWriter(gop, vop, eop));
}


GraphManager::~GraphManager()
{
	rend_ptr_.reset();
	writer_ptr_.reset();
}


boost::filesystem::path GraphManager::graphImageWithOptions(const GraphOptions& options)
{
	HNAGraph graph = HNAGraphFactory::sharedFactory()->getGraph(options);
	boost::filesystem::path folder_path = FileManager::sharedManager()->graph_path();
	boost::filesystem::path g_path =  (*writer_ptr_).writeGraph(graph, folder_path, "graph");
	boost::filesystem::path im_path = (*rend_ptr_).render_graph(g_path, folder_path, "graph");
	return im_path;
}