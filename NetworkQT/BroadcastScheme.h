#pragma once
#include "BroadcastReceiveScheme.h"
#include "BroadcastSendScheme.h"
#include "BroadcastFinishScheme.h"


class BroadcastScheme 
{
	typedef std::unique_ptr<BroadcastSendScheme> send_ptr;
	typedef std::unique_ptr<BroadcastReceiveScheme> receive_ptr;
	typedef std::unique_ptr<BroadcastFinishScheme> finish_ptr;
public:
	BroadcastScheme(send_ptr s, receive_ptr r, finish_ptr f) : f_(std::move(f)), s_(std::move(s)), r_(std::move(r)){};
	virtual ~BroadcastScheme()
	{
		r_.reset();
		s_.reset();
		f_.reset();
	}

	void send(const HNAGraph& graph, const Vertex& node, std::map<Vertex, HNANodeBundle>& messages) const;
	void receive(const HNAGraph& graph, const Vertex& node, const std::map<Vertex, HNANodeBundle>& messages, HNANodeBundle& message) const;
	bool broadcasting_finished(const HNAGraph& graph) const;
	std::string description() const;
private:
	receive_ptr r_;
	send_ptr s_;
	finish_ptr f_;
};

