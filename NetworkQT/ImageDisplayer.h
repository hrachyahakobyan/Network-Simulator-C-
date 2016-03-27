#pragma once
#include <boost/filesystem.hpp>
#include <string>

class ImageDisplayer
{
	typedef boost::filesystem::path path;
public:
	virtual ~ImageDisplayer(){};
	virtual void display_image(const path& path) = 0;
protected:
	ImageDisplayer(const std::string& window) : window_name_(window) {};
	std::string window_name_;
	path image_path;
}; 

