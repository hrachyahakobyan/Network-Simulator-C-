#pragma once
#include "BroadcastSimulation.h"
#include "HNAGraphWriter.h"
#include "CMDGraphRenderer.h"
#include "FileManager.h"

class HNABroadcastSession
{
	typedef std::unique_ptr<BroadcastSimulation> Sim_Ptr;
	typedef std::unique_ptr<HNAGraphWriter> Write_Ptr;
	typedef std::unique_ptr<CMDGraphRenderer> Rend_Ptr;
	typedef boost::filesystem::path Path;
public:
	HNABroadcastSession(Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr, const Path& path) : sim_ptr_(std::move(sim_ptr)), sim_path_(path),
		write_ptr_(std::move(write_ptr)), rend_ptr_(std::move(rend_ptr)), img_count_(0)
	{
		assert(FileManager::sharedManager()->dir_exists(path) && "ERROR: HNABroadcastSession: failed to create directory");
	}

	~HNABroadcastSession();

	bool tick(int tick = 1);
	bool finish(bool write = false);
	void delete_vertex(int vertex);
	void add_vertex();
	void add_edge(int source, int target);
	void delete_edge(int source, int target);
	void set_state(int vertex, int state);

	Path image_path();
	

private:
	Sim_Ptr sim_ptr_;
	Path sim_path_;
	Write_Ptr write_ptr_;
	Rend_Ptr rend_ptr_;
	int img_count_;
};

