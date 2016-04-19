#pragma once
#include "HNAGraphFactory.h"

struct GraphEditAction
{
	enum EditType{ AddVertex, AddEdge, DeleteVertex, DeleteEdge, SetState };
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

class Simulation
{
protected:
	typedef std::unique_ptr<HNAGraph> graph_ptr;
public:
	Simulation();
	Simulation(graph_ptr g) : graph_p_(std::move(g)){};
	virtual ~Simulation();
	virtual bool tick(int count = 1) = 0;
	virtual bool finish(int max_ticks = MAX_TICKS) = 0;
	virtual bool finished() const = 0;
	virtual void edit(const GraphEditAction& edit) = 0;
	virtual const HNAGraph& state() const;
protected:
	graph_ptr graph_p_;
};

