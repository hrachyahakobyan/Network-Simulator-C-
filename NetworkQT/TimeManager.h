#pragma once
#include "Timer.h"

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

	void setTimerIntervalSeconds(int seconds);
	void setTimerIntervalMilliseconds(long milliseconds);
	void stop();
	void start();

	std::string date_string();

private:
	
	static TimeManager* timeManager;
	Timer* _timer;
	ios* _ios;
	duration _interval;

	boost::thread* _thread;

	TimeManager() :_timer(NULL), _thread(NULL), _ios(NULL), _interval(boost::posix_time::seconds(DEFAULT_DURATION_SECONDS)){}
	~TimeManager();

};

