#pragma once
#include "Session.h"
#include "BroadcastSimulation.h"
#include "HNAGraphFactory.h"

class HNABroadcastSession : public Session
{
	typedef std::unique_ptr<BroadcastSimulation> Br_Sim_Ptr;
public:
	HNABroadcastSession(Br_Sim_Ptr sim_ptr, Write_Ptr write_ptr, Rend_Ptr rend_ptr) : 
	Session(std::move(sim_ptr), std::move(write_ptr), std::move(rend_ptr)){};

	static std::unique_ptr<HNABroadcastSession> session(const GraphBuilder::GraphOptions& g_op, const BroadcastSchemeOptions& scheme_options)
	{
		Br_Sim_Ptr sim = BroadcastSimulation::simulation(g_op, scheme_options);
		Write_Ptr write = HNAGraphWriter::defaultWrtier();
		Rend_Ptr rend(new CMDGraphRenderer());
		std::unique_ptr<HNABroadcastSession> session(new HNABroadcastSession(std::move(sim), std::move(write), std::move(rend)));
		return session;
	}
	~HNABroadcastSession();
};

