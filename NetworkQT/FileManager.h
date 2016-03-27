#pragma once
#include "TimeManager.h"

class FileManager
{
	typedef boost::filesystem::path Path;
public:

	/* Get and release */
	static FileManager* sharedManager()
	{
		if (sharedFileManager == 0)
			sharedFileManager = new FileManager;
		return sharedFileManager;
	}
	static void release()
	{
		if (sharedFileManager != 0)
		{
			delete sharedFileManager;
			sharedFileManager = 0;
		}
	}

public:
	bool dir_exists(const Path& p);
	bool file_exists(const Path& p);

	bool make_dir(const Path& p);
	bool make_dir(const Path& p, const std::string& name);

	bool make_file(const Path& p);
	bool make_file(const Path& p, const std::string& name);
	bool make_file(const Path& p, const std::string& name, const std::string& ext);

	bool del_dir(const Path& p);
	bool clear_dir(const Path& p);
	bool del_file(const Path& p);

	Path simulation_path();
	Path graph_path();


private:
	static FileManager* sharedFileManager;
	FileManager();
	~FileManager();
private:
	Path pdata_;
	Path psim_;
	Path pgraph_;
};

