#include "stdafx.h"
#include "Session.h"


Session::Session(Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr) : sim_ptr_(std::move(sim_ptr)),
write_ptr_(std::move(write_ptr)), rend_ptr_(std::move(rend_ptr)), cur_index_(0), eng_index_(0), engines_(RENDER_ENGINES)
{
	sim_path_ = FileManager::sharedManager()->simulation_path();
	assert(FileManager::sharedManager()->dir_exists(sim_path_) && "ERROR: HNABroadcastSession: failed to create directory");
	draw();
}

Session::~Session()
{
	sim_ptr_.reset();
	rend_ptr_.reset();
	write_ptr_.reset();
}

std::string Session::description() const
{
	return (*sim_ptr_).description();
}

bool Session::tick(int count)
{
	if ((*sim_ptr_).finished())
		return true;
	bool tick = (*sim_ptr_).tick(count);
	draw();
	cur_index_ = img_paths_.size() - 1;
	return tick;
}

bool Session::finish()
{
	if ((*sim_ptr_).finished())
		return true;
	int ticks = MAX_TICKS;
	while ((*sim_ptr_).finished() == false && ticks > 0)
	{
		(*sim_ptr_).tick();
		ticks--;
	}
	draw();
	cur_index_ = img_paths_.size() - 1;
	return (*sim_ptr_).finished();
}

void Session::edit(const GraphEditAction& edit)
{
	(*sim_ptr_).edit(edit);
	draw();
	cur_index_ = img_paths_.size() - 1;
}

boost::filesystem::path Session::redraw()
{
	if (cur_index_ == img_paths_.size() - 1)
	{
		eng_index_ = mod(eng_index_ + 1, engines_.size() - 1);
		if (img_paths_.empty() == false)
		{
			Path lastImg = img_paths_.back();
			FileManager::sharedManager()->del_file(lastImg);
			img_paths_.pop_back();
		}
		draw();
		return last();
	}
	return boost::filesystem::path();
}

int Session::mod(int a, int n)
{
	return (a % n) + (a < 0 ? n : 0);
}

boost::filesystem::path Session::last()
{
	return img_paths_[img_paths_.size() - 1];
}

boost::filesystem::path Session::previous()
{
	cur_index_ = cur_index_ > 0 ? cur_index_ - 1 : cur_index_;
	return img_paths_[cur_index_];
}


boost::filesystem::path Session::next()
{
	cur_index_ = cur_index_ >= img_paths_.size() - 1 ? cur_index_ : cur_index_ + 1;
	return img_paths_[cur_index_];
}


void Session::draw()
{
	std::string name = std::to_string(img_paths_.size());
	boost::filesystem::path file_path = (*write_ptr_).writeGraph((*sim_ptr_).state(), sim_path_, name);
	boost::filesystem::path image_path = (*rend_ptr_).render_graph(file_path, sim_path_, name, IMG_EXT_JPG, engines_[eng_index_]);
	img_paths_.push_back(image_path);
}

void Session::save(const boost::filesystem::path& dest)
{
	std::string date = TimeManager::sharedTimeManager()->date_string();
	Path p(dest);
	p.append("/");
	date.append("-simulation");
	p.append(date.c_str());
	FileManager::sharedManager()->copy_dir(sim_path_, p);

}

std::map<std::string, std::pair<Color, std::vector<int>>> Session::data()
{
	return (*sim_ptr_).data();
}

void Session::reset()
{
	(*sim_ptr_).reset();
	cur_index_ = 0;
	img_paths_.clear();
	FileManager::sharedManager()->clear_dir(sim_path_);
	draw();
}