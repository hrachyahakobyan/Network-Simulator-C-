#include "stdafx.h"
#include "Timer.h"


Timer::~Timer()
{
    _timer.cancel();
}

void Timer::start()
{
	initiate();
}

void Timer::handler(const boost::system::error_code& e)
{
	if (e == boost::system::errc::success)
	{
		std::cout << "Timer post notification" << std::endl;
		DefaultNotificationCenter::notificationCenter()->postNotification(TIME_TICK_NOTIFICATION);
		initiate();
	}
}

void Timer::initiate()
{
	_timer.expires_from_now(_interval);
	_timer.async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
}
