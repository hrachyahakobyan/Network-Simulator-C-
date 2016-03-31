#pragma once
#include "BroadcastScheme.h"
#include "HNAGraphFactory.h"

struct GraphEditAction
{
	enum EditType{AddVertex, AddEdge, DeleteVertex, DeleteEdge, SetState};
	EditType type_;
	int v_;
	int src_;
	int targ_;
	int state_;
	GraphEditAction() : type_(AddVertex), v_(0), src_(0), targ_(0), state_(0){};
	static GraphEditAction addVertexAction(int state = 0)
	{
		GraphEditAction action;
		action.state_ = state;
		action.type_ = EditType::AddVertex;
		return action;
	}
	static GraphEditAction addEdgeAction(int s, int t)
	{
		GraphEditAction action;
		action.src_ = s;
		action.targ_ = t;
		action.type_ = EditType::AddEdge;
		return action;
	}
	static GraphEditAction deleteVertexAction(int v)
	{
		GraphEditAction action;
		action.v_ = v;
		action.type_ = EditType::DeleteVertex;
		return action;
	}
	static GraphEditAction deleteEdgeAction(int s, int t)
	{
		GraphEditAction action;
		action.src_ = s;
		action.targ_ = t;
		action.type_ = EditType::DeleteEdge;
		return action;
	}
	static GraphEditAction setStateAction(int v, int s)
	{
		GraphEditAction action;
		action.v_ = v;
		action.state_ = s;
		action.type_ = EditType::SetState;
		return action;
	}
};

class BroadcastSimulation
{
	typedef std::unique_ptr<BroadcastScheme> scheme_p;
	typedef std::unique_ptr<HNAGraph> graph_ptr;
public:

	BroadcastSimulation(graph_ptr g, scheme_p p) : graph_p_(std::move(g)),scheme_p_(std::move(p))
	{
		(*graph_p_).properties().broadcast_type_ = (*scheme_p_).description();
	}
	
	static std::unique_ptr<BroadcastSimulation> simulation(const GraphOptions& g_options, const BroadcastSchemeOptions& s_options)
	{
		graph_ptr gptr = HNAGraphFactory::sharedFactory()->getGraph(g_options);
		scheme_p sptr = BroadcastScheme::scheme(s_options);
		std::unique_ptr<BroadcastSimulation> sim_ptr(new BroadcastSimulation(std::move(gptr), std::move(sptr)));
		return sim_ptr;
	}

	virtual ~BroadcastSimulation();
	virtual bool tick(int count = 1);
	virtual bool finish(int max_ticks = MAX_TICKS);
	virtual bool finished() const;
	virtual const HNAGraph& state() const;
	virtual void edit(const GraphEditAction& edit);


private:
	graph_ptr graph_p_;
	scheme_p scheme_p_;
private:
	 void add_vertex();
	 void delete_vertex(int vertex);
	 void add_edge(int source, int target);
	 void delete_edge(int source, int target);
	 void set_state(int vertex, int state);
};

