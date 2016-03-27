#include "stdafx.h"
#include "FileManager.h"


FileManager* FileManager::sharedFileManager = 0;

FileManager::FileManager()
{
	pdata_ = ("../data");
	psim_ = pdata_; psim_.concat("/simulations");
	pgraph_ = pdata_; pgraph_.concat("/graphs");

	std::cout << pdata_ << std::endl;
	std::cout << psim_ << std::endl;
	std::cout << pgraph_ << std::endl;

	if (dir_exists(pdata_) == false)
		make_dir(pdata_);
	if (dir_exists(psim_) == false)
		make_dir(psim_);
	if (dir_exists(pgraph_) == false)
		make_dir(pgraph_);
	assert(dir_exists(pdata_) && dir_exists(psim_) && dir_exists(pgraph_) && "ERROR: FileManager: Setup failed");
}

FileManager::~FileManager()
{
}


bool FileManager::dir_exists(const Path& p)
{
	return boost::filesystem::exists(p) && boost::filesystem::is_directory(p);
}

bool FileManager::file_exists(const Path& p)
{
	return boost::filesystem::exists(p) && boost::filesystem::is_regular_file(p);
}

bool FileManager::make_dir(const Path& p)
{
	if (boost::filesystem::exists(p) && boost::filesystem::is_directory(p))
		return false;
	return boost::filesystem::create_directory(p);
}

bool FileManager::make_dir(const Path& p, const std::string& name)
{
	Path dp(p);
	dp.concat("/");
	dp.concat(name);
	return make_dir(dp);
}

bool FileManager::make_file(const Path& p)
{
	if (boost::filesystem::exists(p) && boost::filesystem::is_regular_file(p))
		return false;
	try
	{
		std::fstream f;
		f.open(p.c_str(), std::ios::out);
		f << std::flush;
		f.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

bool FileManager::make_file(const Path& p, const std::string& name)
{
	Path fp(p);
	fp.concat("/");
	fp.concat(name);
	return make_file(fp);
}

bool FileManager::make_file(const Path& p, const std::string& name, const std::string& ext)
{
	Path fp(p);
	fp.concat("/");
	fp.concat(name);
	fp.concat(".");
	fp.concat(ext);
	return make_file(fp);
}

bool FileManager::del_dir(const Path& p)
{
	if (!(boost::filesystem::exists(p) && boost::filesystem::is_directory(p)))
		return false;
	try
	{
		boost::filesystem::remove_all(p);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
	return true;
}


bool FileManager::clear_dir(const Path& p)
{
	if (!(boost::filesystem::exists(p) && boost::filesystem::is_directory(p)))
		return false;
	for (boost::filesystem::directory_iterator end_dir_it, it(p); it != end_dir_it; ++it) {
		try
		{
			boost::filesystem::remove_all(it->path());
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return false;
		}
	}
	return true;
}

bool FileManager::del_file(const Path& p)
{
	return file_exists(p) && boost::filesystem::remove(p);
}


boost::filesystem::path FileManager::simulation_path()
{
	std::string time_string = TimeManager::sharedTimeManager()->date_string();
	time_string.append("-simulation");
	Path path(psim_);
	path.append("/");
	path.append(time_string);
	make_dir(path);
	return path;
}


boost::filesystem::path FileManager::graph_path()
{
	std::string time_string = TimeManager::sharedTimeManager()->date_string();
	time_string.append("-graph");
	Path path(pgraph_);
	path.append("/");
	path.append(time_string);
	make_dir(path);
	return path;
}

bool FileManager::copy_dir(const boost::filesystem::path& source, const boost::filesystem::path& destination)
{
	namespace fs = boost::filesystem;
	try
	{
		// Check whether the function call is valid
		if (
			!fs::exists(source) ||
			!fs::is_directory(source)
			)
		{
			std::cerr << "Source directory " << source.string()
				<< " does not exist or is not a directory." << '\n'
				;
			return false;
		}
		if (fs::exists(destination))
		{
			std::cerr << "Destination directory " << destination.string()
				<< " already exists." << '\n'
				;
			return false;
		}
		// Create the destination directory
		if (!fs::create_directory(destination))
		{
			std::cerr << "Unable to create destination directory"
				<< destination.string() << '\n'
				;
			return false;
		}
	}
	catch (fs::filesystem_error const & e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
	// Iterate through the source directory
	for (
		fs::directory_iterator file(source);
		file != fs::directory_iterator(); ++file
		)
	{
		try
		{
			fs::path current(file->path());
			if (fs::is_directory(current))
			{
				// Found directory: Recursion
				if (
					!copy_dir(
					current,
					destination / current.filename()
					)
					)
				{
					return false;
				}
			}
			else
			{
				// Found file: Copy
				fs::copy_file(
					current,
					destination / current.filename()
					);
			}
		}
		catch (fs::filesystem_error const & e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return true;
}