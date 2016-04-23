#pragma once
#include "Session.h"
#include "DiseaseFactory.h"

class DiseaseSession : public Session
{
	typedef std::unique_ptr<DiseaseSimulation> Dis_Sim_Ptr;
public:
	DiseaseSession(Dis_Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr) :
		Session(std::move(sim_ptr), std::move(write_ptr), std::move(rend_ptr)){};

	static std::unique_ptr<DiseaseSession> session(const GraphBuilder::GraphOptions& g_op, const DiseaseSimulation::DiseaseOptions& d_op)
	{
		Dis_Sim_Ptr sim = DiseaseFactory::sharedFactory()->diseaseSimulation(g_op, d_op);
		Write_Ptr write = HNAGraphWriter::defaultWrtier();
		Rend_Ptr rend(new CMDGraphRenderer());
		std::unique_ptr<DiseaseSession> session(new DiseaseSession(std::move(sim), std::move(write), std::move(rend)));
		return session;
	}
	~DiseaseSession();
};

