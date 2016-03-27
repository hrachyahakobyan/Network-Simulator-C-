#pragma once

class GraphRenderer
{
	typedef boost::filesystem::path path;
public:
	virtual ~GraphRenderer(){};
	virtual path render_graph(const path& src_path, const path& dest_path, const std::string& name, const std::string& img_ext = IMG_EXT_JPG) = 0;
protected:
	GraphRenderer(){};
};

