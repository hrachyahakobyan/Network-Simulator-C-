#include "stdafx.h"
#include "CMDGraphRenderer.h"

boost::filesystem::path CMDGraphRenderer::render_graph(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext, const std::string& engine)
{
	assert(boost::filesystem::exists(src_path) && boost::filesystem::is_regular_file(src_path) && "ERROR: CMDGraphRenderer: source path does not exist or is not a file");

	std::string command;
	std::string image_path;
	construct_command(src_path, dst_path, name, img_ext, engine, command, image_path);
	system(command.c_str());
	return image_path;
}

void CMDGraphRenderer::construct_command(const path& src_path, const path& dst_path, const std::string& name, const std::string& img_ext, const std::string& engine, std::string& command, std::string& image_path)
{
	command.clear();
	image_path = dst_path.string();
	image_path.append("/");
	image_path.append(name);
	image_path.append(".");
	image_path.append(img_ext);
	command.append(engine);
	command.append(" -T");
	command.append(img_ext);
	command.append(" ");
	command.append(src_path.string());
	command.append(" -o ");
	command.append(image_path);
	command.append(" -Goutputorder=edgesfirst");
}