#pragma once
#include "GraphRenderer.h"

class CMDGraphRenderer : public GraphRenderer
{
	typedef boost::filesystem::path path;
public:
	boost::filesystem::path render_graph(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext = IMG_EXT_JPG, const std::string& engine = "sfdp");
	CMDGraphRenderer(){};
	~CMDGraphRenderer(){};
private:
	void construct_command(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext, const std::string& engine, std::string& output, std::string& image_path);
};

