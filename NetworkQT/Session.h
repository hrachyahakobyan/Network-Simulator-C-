#pragma once
#include "Simulation.h"
#include "CMDGraphRenderer.h"
#include "HNAGraphWriter.h"

class Session
{
protected:
	typedef std::unique_ptr<Simulation> Sim_Ptr;
	typedef std::unique_ptr<HNAGraphWriter> Write_Ptr;
	typedef std::unique_ptr<CMDGraphRenderer> Rend_Ptr;
	typedef boost::filesystem::path Path;
public:
	Session(Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr);
	virtual ~Session();
public:
	virtual std::string description() const;
	virtual std::map<std::string, int> allowedStates() const;
	virtual int edgeCount() const;
	virtual int vertexCount() const;
	virtual bool tick(int tick = 1);
	virtual bool finish();
	virtual void edit(const GraphEditAction& edit);
	virtual void save(const boost::filesystem::path& dest);
	virtual boost::filesystem::path redraw();
	virtual boost::filesystem::path last();
	virtual boost::filesystem::path previous();
	virtual boost::filesystem::path next();
	virtual std::map<std::string, std::pair<Color, std::vector<int>>> data();
	virtual void reset();
	bool shouldRender;
protected:
	Sim_Ptr sim_ptr_;
	Write_Ptr write_ptr_;
	Rend_Ptr rend_ptr_;
	std::vector<Path> img_paths_;
	std::vector<std::string> engines_;
	Path sim_path_;
	int cur_index_;
	int eng_index_;
	void draw();
	int mod(int a, int n);
};

