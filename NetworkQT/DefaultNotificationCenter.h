#pragma once

class Observer
{
public:
	virtual void notify(const std::string &_notificationName) = 0;
};


class SomeObserver : public Observer
{
public:
	static int count;
	void notify(const std::string &_notificationName)
	{
		std::cout << "I have been notified" << std::endl;
	}
	SomeObserver()
	{
		SomeObserver::count++;
		std::cout << SomeObserver::count << std::endl;
		std::cout << "Defulat constructor called" << std::endl;
	}
	~SomeObserver()
	{
		std::cout << "Dealloced" << std::endl;
	}

	SomeObserver(const SomeObserver& otherObserver)
	{
		std::cout << "Copy constructor called" << std::endl;
	}

	SomeObserver& operator=(const SomeObserver& otherObserver)
	{
		std::cout << "Assignment operator= called" << std::endl;
	}
};


class DefaultNotificationCenter
{
public:
	static DefaultNotificationCenter* notificationCenter()
	{
		if (sharedNotificationCenter == 0)
			sharedNotificationCenter = new DefaultNotificationCenter;
		return sharedNotificationCenter;
	}
	static void release()
	{
		if (sharedNotificationCenter != 0)
		{
			delete sharedNotificationCenter;
			sharedNotificationCenter = 0;
		}
	}
	void addObserver(Observer* const _observer, const std::string &_notificationName);
	void removeObserver(Observer* const _observer, const std::string &_notificationName);

	void postNotification(const std::string& _notificationName);

private:
	static DefaultNotificationCenter* sharedNotificationCenter;
	DefaultNotificationCenter();
	~DefaultNotificationCenter();
	std::unordered_map<std::string, std::set<Observer*>> observerMap;
};

