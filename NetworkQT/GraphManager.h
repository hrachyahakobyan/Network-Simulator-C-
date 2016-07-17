#pragma once
#include "HNAGraphWriter.h"
#include "GraphBuilder.h"
#include "CMDGraphRenderer.h"
#include "FileManager.h"

class GraphManager
{
public:
	static GraphManager* sharedManager()
	{
		if (_graphManager == 0)
			_graphManager = new GraphManager();
		return _graphManager;
	}

	static void release()
	{
		if (_graphManager != 0)
		{
			delete _graphManager;
			_graphManager = 0;
		}
	}

	void graphImageWithOptions(const GraphBuilder::GraphOptions& options, boost::filesystem::path& image_path, boost::filesystem::path& folder_path);
	void saveGraphImage(const boost::filesystem::path& src_path, const boost::filesystem::path& dst_path);

private:
	static GraphManager* _graphManager;
	std::unique_ptr<HNAGraphWriter> writer_ptr_;
	std::unique_ptr<CMDGraphRenderer> rend_ptr_;
	GraphManager();
	~GraphManager();
};

