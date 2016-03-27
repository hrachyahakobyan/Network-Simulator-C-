#include "stdafx.h"
#include "TimeManager.h"

TimeManager *TimeManager::timeManager = 0;

TimeManager::~TimeManager()
{
	stop();
}

std::string TimeManager::date_string()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y-%H-%M-%S", &tstruct);
	return buf;
}

void TimeManager::setTimerIntervalSeconds(int seconds)
{
	if (seconds < 1)
		std::cout << "Invalid wait time in seconds, must be at least 1" << std::endl;
	else if (seconds > MAX_DURATION_SECONDS)
		std::cout << "Invalid wait time in seconds, must be not more than " << MAX_DURATION_SECONDS << std::endl;
	else
	{
		_interval = boost::posix_time::seconds(seconds);
		start();
	}

}

void TimeManager::setTimerIntervalMilliseconds(long milliseconds)
{
	if (milliseconds < MIN_DURATION_MILLISECONDS)
		std::cout << "Invalid wait time in milliseconds, must be at least " << MIN_DURATION_MILLISECONDS << std::endl;
	else if (milliseconds > MAX_DURATION_MILLISECONDS)
		std::cout << "Invalid wait time in milliseconds, must be not more than " << MAX_DURATION_MILLISECONDS << std::endl;
	else
	{
		 _interval = boost::posix_time::milliseconds(milliseconds);
		 start();
	}
}

void TimeManager::start()
{
	stop();
	_ios = new boost::asio::io_service;
	_timer = new Timer(*_ios, _interval);
	_timer->start();
	_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, _ios));
}

void TimeManager::stop()
{
	try
	{
		if (_ios != NULL)
		{
			_ios->stop();
			if (_thread != NULL)
				_thread->join();
			if (_timer != NULL)
			{
				delete _timer;
				_timer = NULL;
			}
			delete _ios;
			_ios = NULL;
		}
		if (_thread != NULL)
		{
			delete _thread;
			_thread = NULL;
		}
	}
	catch (std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}


