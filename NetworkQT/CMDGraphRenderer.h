#pragma once
#include "GraphRenderer.h"

class CMDGraphRenderer : public GraphRenderer
{
	typedef boost::filesystem::path path;
public:
	path render_graph(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext = IMG_EXT_JPG);
	CMDGraphRenderer(){};
	~CMDGraphRenderer(){};
private:
	void construct_command(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext, std::string& output, std::string& image_path);
};

