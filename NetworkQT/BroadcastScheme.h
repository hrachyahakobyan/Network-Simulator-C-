#pragma once
#include "BroadcastFinishSchemeFactory.h"
#include "BroadcastReceiveSchemeFactory.h"
#include "BroadcastSendSchemeFactory.h"


struct BroadcastSchemeOptions
{
	std::string send_type_;
	std::string receive_type_;
	std::string finish_type_;
	BroadcastSchemeOptions(const std::string& s_t, const std::string& r_t, const std::string& f_t) : send_type_(s_t), receive_type_(r_t), finish_type_(f_t){};
	BroadcastSchemeOptions() : send_type_(""), receive_type_(""), finish_type_(""){};
};


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

	static std::unique_ptr<BroadcastScheme> scheme(std::unique_ptr<BroadcastSendScheme> s, std::unique_ptr<BroadcastReceiveScheme> r, std::unique_ptr<BroadcastFinishScheme> f)
	{
		std::unique_ptr<BroadcastScheme> scheme(new BroadcastScheme(std::move(s), std::move(r), std::move(f)));
		return scheme;
	}

	static std::unique_ptr<BroadcastScheme> scheme(const BroadcastSchemeOptions& options)
	{
		finish_ptr f = BroadcastFinishSchemeFactory::sharedFactory()->createFinishScheme(options.finish_type_);
		send_ptr s = BroadcastSendSchemeFactory::sharedFactory()->createSendScheme(options.send_type_);
		receive_ptr r = BroadcastReceiveSchemeFactory::sharedFactory()->createrRecieveScheme(options.receive_type_);
		return BroadcastScheme::scheme(std::move(s), std::move(r), std::move(f));
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

