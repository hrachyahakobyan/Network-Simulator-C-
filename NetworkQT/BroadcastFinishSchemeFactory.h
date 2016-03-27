#pragma once
#include "BroadcastFinishSchemeM.h"

class BroadcastFinishSchemeFactory
{
public:
	static BroadcastFinishSchemeFactory* sharedFactory()
	{
		if (sharedSchemeFactory == 0)
			sharedSchemeFactory = new BroadcastFinishSchemeFactory();
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
	std::unique_ptr<BroadcastFinishScheme> createFinishScheme(const std::string& name)
	{
		std::map<std::string, PCreateFunc>::iterator it = func_map.find(name);
		return std::unique_ptr<BroadcastFinishScheme>(it->second());
	}
	template<typename T>
	void Register(const std::string& name)
	{
		func_map[name] = &CreateFunc<T>;
	}

private:
	template <typename T>
	static BroadcastFinishScheme* CreateFunc()
	{
		return new T;
	}
	static BroadcastFinishSchemeFactory* sharedSchemeFactory;
	BroadcastFinishSchemeFactory()
	{
		Register<BroadcastFinishSchemeM>(FINISH_SCHEME_M);
	}
	~BroadcastFinishSchemeFactory()
	{
		func_map.clear();
	}

private:
	typedef BroadcastFinishScheme* (*PCreateFunc)();
	std::map<std::string, PCreateFunc> func_map;
};

