#include "stdafx.h"
#include "CVImageDisplayer.h"

CVImageDisplayer::CVImageDisplayer() : ImageDisplayer("Graph")
{
	namedWindow(window_name_, WINDOW_NORMAL);
}

CVImageDisplayer::CVImageDisplayer(const std::string& window) : ImageDisplayer(window)
{
	namedWindow(window_name_, WINDOW_NORMAL);
}


CVImageDisplayer::~CVImageDisplayer()
{
	image_.release();
	destroyAllWindows();
}

void CVImageDisplayer::display_image(const path& path)
{
	if (boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path))
	{
		image_ = imread(path.string(), 1);
		if (image_.data == NULL)
		{
			image_.release();
			std::cout << "Invalid image at path " << path << std::endl;
		}
		else
		{
			imshow(window_name_, image_);
		}
	}
	else
		std::cout << "Invalid image path " << path << std::endl;
}
