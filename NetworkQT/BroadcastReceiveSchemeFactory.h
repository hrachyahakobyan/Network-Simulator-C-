#pragma once
#include "BroadcastReceiveSchemeM.h"


class BroadcastReceiveSchemeFactory
{
public:
	static BroadcastReceiveSchemeFactory* sharedFactory()
	{
		if (sharedSchemeFactory == 0)
			sharedSchemeFactory = new BroadcastReceiveSchemeFactory();
		return sharedSchemeFactory;
	}
	static void release()
	{
		if (sharedSchemeFactory != 0)
		{
			delete sharedSchemeFactory;
			sharedSchemeFactory = 0;
		}
	}
	std::unique_ptr<BroadcastReceiveScheme> createrRecieveScheme(const std::string& name)
	{
		std::map<std::string, PCreateFunc>::iterator it = func_map.find(name);
		return std::unique_ptr<BroadcastReceiveScheme>(it->second());
	}
	template<typename T>
	void Register(const std::string& name)
	{
		func_map[name] = &CreateFunc<T>;
	}

private:
	template <typename T>
	static BroadcastReceiveScheme* CreateFunc()
	{
		return new T;
	}
	static BroadcastReceiveSchemeFactory* sharedSchemeFactory;
	BroadcastReceiveSchemeFactory()
	{
		Register<BroadcastReceiveSchemeM>(RECEIVE_SCHEME_M);
	}
	~BroadcastReceiveSchemeFactory()
	{
		func_map.clear();
	}

private:
	typedef BroadcastReceiveScheme* (*PCreateFunc)();
	std::map<std::string, PCreateFunc> func_map;
};

