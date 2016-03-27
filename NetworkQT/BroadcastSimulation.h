#pragma once
#include "BroadcastScheme.h"

class BroadcastSimulation
{
	typedef std::unique_ptr<BroadcastScheme> scheme_p;
public:
	BroadcastSimulation(const HNAGraph& g, scheme_p p) : g_(g), scheme_p_(std::move(p))
	{
		g_.properties().broadcast_type_ = (*scheme_p_).description();
	}
	
	virtual ~BroadcastSimulation();
	virtual bool tick(int count = 1);
	virtual bool finish(int max_ticks = MAX_TICKS);
	virtual bool finished() const;
	virtual const HNAGraph& state() const;

	virtual void add_vertex();
	virtual void delete_vertex(int vertex);
	virtual void add_edge(int source, int target);
	virtual void delete_edge(int source, int target);
	virtual void set_state(int vertex, int state);

private:
	HNAGraph g_;
	scheme_p scheme_p_;
};

