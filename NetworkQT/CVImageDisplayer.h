#pragma once
#include "ImageDisplayer.h"

using namespace cv;

class CVImageDisplayer : public ImageDisplayer
{
	typedef boost::filesystem::path path;
public:
	CVImageDisplayer();
	CVImageDisplayer(const std::string& window);
	~CVImageDisplayer();
	void display_image(const path& path);
private:
	Mat image_;
};

