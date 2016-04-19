#pragma once
#include "Session.h"
#include "DiseaseSimulation.h"

class DiseaseSession : public Session
{
	typedef std::unique_ptr<DiseaseSimulation> Dis_Sim_Ptr;
public:
	DiseaseSession(Dis_Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr) :
		Session(std::move(sim_ptr), std::move(write_ptr), std::move(rend_ptr)){};
	~DiseaseSession();
};

