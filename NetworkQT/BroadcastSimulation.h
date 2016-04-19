#pragma once
#include "BroadcastScheme.h"
#include "Simulation.h"


class BroadcastSimulation : public Simulation
{
	typedef std::unique_ptr<BroadcastScheme> scheme_p;
public:

	BroadcastSimulation(graph_ptr g, scheme_p p) : Simulation(std::move(g)), scheme_p_(std::move(p))
	{
		(*graph_p_).properties().broadcast_type_ = (*scheme_p_).description();
	}
	
	static std::unique_ptr<BroadcastSimulation> simulation(const GraphBuilder::GraphOptions& g_options, const BroadcastSchemeOptions& s_options)
	{
		graph_ptr gptr = HNAGraphFactory::sharedFactory()->getGraph(g_options);
		scheme_p sptr = BroadcastScheme::scheme(s_options);
		std::unique_ptr<BroadcastSimulation> sim_ptr(new BroadcastSimulation(std::move(gptr), std::move(sptr)));
		return sim_ptr;
	}

	~BroadcastSimulation();
	bool tick(int count = 1);
	bool finish(int max_ticks = MAX_TICKS);
	bool finished() const;
	void edit(const GraphEditAction& edit);


private:
	scheme_p scheme_p_;
private:
	 void add_vertex();
	 void delete_vertex(int vertex);
	 void add_edge(int source, int target);
	 void delete_edge(int source, int target);
	 void set_state(int vertex, int state);
};

