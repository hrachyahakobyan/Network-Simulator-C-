#pragma once
#include "BroadcastSendSchemeM1.h"
#include "BroadcastSendSchemeM2.h"
#include "BroadcastSendSchemeM3.h"

class BroadcastSendSchemeFactory
{
public:
	static BroadcastSendSchemeFactory* sharedFactory()
	{
		if (sharedSchemeFactory == 0)
			sharedSchemeFactory = new BroadcastSendSchemeFactory();
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
	std::unique_ptr<BroadcastSendScheme> createSendScheme(const std::string& name)
	{
		std::map<std::string, PCreateFunc>::iterator it = func_map.find(name);
		return std::unique_ptr<BroadcastSendScheme>(it->second());
	}
	template<typename T>
	void Register(const std::string& name)
	{
		func_map[name] = &CreateFunc<T>;
	}

private:
	template <typename T>
	static BroadcastSendScheme* CreateFunc()
	{
		return new T;
	}
	static BroadcastSendSchemeFactory* sharedSchemeFactory;
	BroadcastSendSchemeFactory()
	{
		Register<BroadcastSendSchemeM1>(SEND_SCHEME_M1);
		Register<BroadcastSendSchemeM2>(SEND_SCHEME_M2);
		Register<BroadcastSendSchemeM3>(SEND_SCHEME_M3);
	}
	~BroadcastSendSchemeFactory()
	{
		func_map.clear();
	}

private:
	typedef BroadcastSendScheme* (*PCreateFunc)();
	std::map<std::string, PCreateFunc> func_map;
};

