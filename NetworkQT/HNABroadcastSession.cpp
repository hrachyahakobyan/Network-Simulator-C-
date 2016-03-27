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
	return (*sim_ptr_).tick(count);
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
			image_path();
			ticks--;
		}
		return (*sim_ptr_).finished();
	}
}

void HNABroadcastSession::add_edge(int source, int target)
{
	(*sim_ptr_).add_edge(source, target);
}

void HNABroadcastSession::add_vertex()
{
	(*sim_ptr_).add_vertex();
}

void HNABroadcastSession::delete_vertex(int vertex)
{
	(*sim_ptr_).delete_vertex(vertex);
}

void HNABroadcastSession::delete_edge(int source, int target)
{
	(*sim_ptr_).delete_edge(source, target);
}


void HNABroadcastSession::set_state(int vertex, int state)
{
	(*sim_ptr_).set_state(vertex, state);
}

boost::filesystem::path HNABroadcastSession::image_path()
{
	std::string name = std::to_string(img_count_);
	boost::filesystem::path file_path = (*write_ptr_).writeGraph((*sim_ptr_).state(), sim_path_, name);
	boost::filesystem::path image_path = (*rend_ptr_).render_graph(file_path, sim_path_, to_string(img_count_));
	img_count_++;
	return image_path;
}