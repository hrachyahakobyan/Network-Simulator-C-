#pragma once

class Timer
{
	typedef boost::asio::io_service ios;
	typedef boost::asio::deadline_timer timer;
	typedef timer::duration_type duration;
	
	friend class TimeManager;

private:

	Timer(ios& ios, duration interval) : _ios(ios), _timer(timer(ios)), _interval(interval)
	{
	
	};
	~Timer();

	void start();

	ios& _ios;
	timer _timer;
	duration _interval;

	void initiate();
	void handler(const boost::system::error_code& e);
	
};

