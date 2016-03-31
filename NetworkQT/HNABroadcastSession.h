#pragma once
#include "BroadcastSimulation.h"
#include "HNAGraphWriter.h"
#include "CMDGraphRenderer.h"
#include "FileManager.h"
#include "HNAGraphFactory.h"

class HNABroadcastSession
{
	typedef std::unique_ptr<BroadcastSimulation> Sim_Ptr;
	typedef std::unique_ptr<HNAGraphWriter> Write_Ptr;
	typedef std::unique_ptr<CMDGraphRenderer> Rend_Ptr;
	typedef boost::filesystem::path Path;
public:
	HNABroadcastSession(Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr) : sim_ptr_(std::move(sim_ptr)),
		write_ptr_(std::move(write_ptr)), rend_ptr_(std::move(rend_ptr)), cur_index_(0)
	{
		sim_path_ = FileManager::sharedManager()->simulation_path();
		assert(FileManager::sharedManager()->dir_exists(sim_path_) && "ERROR: HNABroadcastSession: failed to create directory");
		draw();
	}

	static std::unique_ptr<HNABroadcastSession> session(const GraphOptions& g_op, const BroadcastSchemeOptions& scheme_options)
	{
		Sim_Ptr sim = BroadcastSimulation::simulation(g_op, scheme_options);
		Write_Ptr write = HNAGraphWriter::defaultWrtier();
		Rend_Ptr rend(new CMDGraphRenderer());
		std::unique_ptr<HNABroadcastSession> session(new HNABroadcastSession(std::move(sim), std::move(write), std::move(rend)));
		return session;
	}

	~HNABroadcastSession();

	bool tick(int tick = 1);
	bool finish(bool write = false);
	void edit(const GraphEditAction& edit);
	void save(const boost::filesystem::path& dest);
	boost::filesystem::path last();
	boost::filesystem::path previous();
	boost::filesystem::path next();

private:
	Sim_Ptr sim_ptr_;
	Write_Ptr write_ptr_;
	Rend_Ptr rend_ptr_;
	std::vector<Path> img_paths_;
	Path sim_path_;
	int cur_index_;
	void draw();
};

