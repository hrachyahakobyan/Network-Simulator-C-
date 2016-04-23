#include "stdafx.h"
#include "GraphManager.h"
#include "HNAGraphFactory.h"

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


void GraphManager::graphImageWithOptions(const GraphBuilder::GraphOptions& options, boost::filesystem::path& image_path, boost::filesystem::path& f_path)
{
	std::unique_ptr<HNAGraph> graph = HNAGraphFactory::sharedFactory()->getGraph(options);
	boost::filesystem::path folder_path = FileManager::sharedManager()->graph_path();
	boost::filesystem::path g_path =  (*writer_ptr_).writeGraph(*graph, folder_path, "graph");
	boost::filesystem::path im_path = (*rend_ptr_).render_graph(g_path, folder_path, "graph");
	image_path = im_path;
	f_path = folder_path;
	graph.reset();
}

void GraphManager::saveGraphImage(const boost::filesystem::path& src_path, const boost::filesystem::path& dst_path)
{
	std::string time_string = TimeManager::sharedTimeManager()->date_string();
	time_string.append("-graph");
	boost::filesystem::path destination(dst_path);
	destination.append("/");
	destination.append(time_string);
	FileManager::sharedManager()->copy_dir(src_path, destination);
}