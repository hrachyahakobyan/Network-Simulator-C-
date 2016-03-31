#include "stdafx.h"
#include "HNABroadcastSession.h"


HNABroadcastSession::~HNABroadcastSession()
{
	sim_ptr_.reset();
	rend_ptr_.reset();
	write_ptr_.reset();
}


bool HNABroadcastSession::tick(int count)
{
	bool tick = (*sim_ptr_).tick(count);
	draw();
	cur_index_ = img_paths_.size() - 1;
	return tick;
}

bool HNABroadcastSession::finish(bool write)
{
	if (write == false)
		return (*sim_ptr_).finish();
	else
	{
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
}

void HNABroadcastSession::edit(const GraphEditAction& edit)
{
	(*sim_ptr_).edit(edit);
	draw();
}

boost::filesystem::path HNABroadcastSession::last()
{
	return img_paths_[img_paths_.size() - 1];
}

boost::filesystem::path HNABroadcastSession::previous()
{
	cur_index_ = cur_index_ > 0 ? cur_index_ - 1 : cur_index_;
	return img_paths_[cur_index_];
}


boost::filesystem::path HNABroadcastSession::next()
{
	cur_index_ = cur_index_ >= img_paths_.size() - 1 ? cur_index_ : cur_index_ + 1;
	return img_paths_[cur_index_];
}


void HNABroadcastSession::draw()
{
	std::string name = std::to_string(img_paths_.size());
	boost::filesystem::path file_path = (*write_ptr_).writeGraph((*sim_ptr_).state(), sim_path_, name);
	boost::filesystem::path image_path = (*rend_ptr_).render_graph(file_path, sim_path_, name);
	img_paths_.push_back(image_path);
}

void HNABroadcastSession::save(const boost::filesystem::path& dest)
{
	std::string date = TimeManager::sharedTimeManager()->date_string();
	Path p(dest);
	p.append("/");
	p.append(date);
	p.append("-simulation");
	FileManager::sharedManager()->copy_dir(sim_path_, p);

}