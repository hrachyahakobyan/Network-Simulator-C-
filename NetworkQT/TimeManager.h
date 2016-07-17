#pragma once

class TimeManager
{
	typedef boost::asio::io_service ios;
	typedef boost::asio::deadline_timer timer;
	typedef timer::duration_type duration;

public:
	static TimeManager* sharedTimeManager()
	{
		if (timeManager == 0)
		{
			timeManager = new TimeManager();
		}
		return timeManager;
	}

	static void release()
	{
		if (timeManager != 0)
		{
			delete timeManager;
			timeManager = 0;
		}
	}

	std::string date_string();

private:
	
	static TimeManager* timeManager;

	TimeManager(){};
	~TimeManager();

};

