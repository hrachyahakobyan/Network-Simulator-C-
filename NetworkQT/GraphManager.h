#pragma once
#include "HNAGraphWriter.h"
#include "HNAGraphFactory.h"
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

	boost::filesystem::path graphImageWithOptions(const GraphOptions& options);

private:
	static GraphManager* _graphManager;
	std::unique_ptr<HNAGraphWriter> writer_ptr_;
	std::unique_ptr<CMDGraphRenderer> rend_ptr_;
	GraphManager();
	~GraphManager();
};

