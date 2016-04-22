#pragma once
#include "DiseaseSimulationSIR.h"
#include "HNAGraphFactory.h"

class DiseaseFactory
{
public:
	static DiseaseFactory* sharedFactory()
	{
		if (sharedDiseaseFactory == 0)
			sharedDiseaseFactory = new DiseaseFactory;
		return sharedDiseaseFactory;
	}

	static void release()
	{
		if (sharedDiseaseFactory != 0)
		{
			delete sharedDiseaseFactory;
			sharedDiseaseFactory = 0;
		}
	}

	std::unique_ptr<DiseaseSimulation> diseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& d_options)
	{
		std::map<DiseaseSimulation::ModelType, PCreateFunc>::iterator it = func_map.find(d_options.type);
		return std::unique_ptr<DiseaseSimulation>(it->second(g_options, d_options));
	}
	
	template<typename T>
	void Register(DiseaseSimulation::ModelType type)
	{
		func_map[type] = &CreateFunc<T>;
	}

private:
	static DiseaseFactory* sharedDiseaseFactory;
	DiseaseFactory();
	~DiseaseFactory(); 

	template <typename T>
	static DiseaseSimulation* CreateFunc(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& d_options)
	{
		return new T(g_options, d_options);
	}


private:
	typedef DiseaseSimulation* (*PCreateFunc)(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& d_options);
	std::map<DiseaseSimulation::ModelType, PCreateFunc> func_map;
};

