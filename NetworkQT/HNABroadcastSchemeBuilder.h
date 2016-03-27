#pragma once
#include "BroadcastScheme.h"
#include "BroadcastFinishSchemeFactory.h"
#include "BroadcastReceiveSchemeFactory.h"
#include "BroadcastSendSchemeFactory.h"

struct BroadcastSchemeOptions
{
public:
	std::string send_type_;
	std::string receive_type_;
	std::string finish_type_;
	BroadcastSchemeOptions(std::string s_t, std::string r_t, std::string f_t) : send_type_(s_t), receive_type_(r_t), finish_type_(f_t){};
};


class HNABroadcastSchemeBuilder
{
	typedef std::unique_ptr<BroadcastScheme> scheme_ptr;
	typedef std::unique_ptr<BroadcastSendScheme> send_ptr;
	typedef std::unique_ptr<BroadcastFinishScheme> finish_ptr;
	typedef std::unique_ptr<BroadcastReceiveScheme> receive_ptr;
public:
	static HNABroadcastSchemeBuilder* sharedSchemeBuilder()
	{
		if (sharedBuilder == 0)
			sharedBuilder = new HNABroadcastSchemeBuilder();
		return sharedBuilder;
	}
	static void release()
	{
		if (sharedBuilder != 0)
		{
			delete sharedBuilder;
			sharedBuilder = 0;
		}
	}

	scheme_ptr getScheme(const BroadcastSchemeOptions& options)
	{
		send_ptr s = sFac_->createSendScheme(options.send_type_);
		finish_ptr f = fFac_->createFinishScheme(options.finish_type_);
		receive_ptr r = rFac_->createrRecieveScheme(options.receive_type_);
		scheme_ptr scheme(new BroadcastScheme(std::move(s), std::move(r), std::move(f)));
		return scheme;
	}

private:
	static HNABroadcastSchemeBuilder* sharedBuilder;
	HNABroadcastSchemeBuilder()
	{
		fFac_ = BroadcastFinishSchemeFactory::sharedFactory();
		rFac_ = BroadcastReceiveSchemeFactory::sharedFactory();
		sFac_ = BroadcastSendSchemeFactory::sharedFactory();
	}
	~HNABroadcastSchemeBuilder();
	BroadcastFinishSchemeFactory* fFac_;
	BroadcastReceiveSchemeFactory* rFac_;
	BroadcastSendSchemeFactory* sFac_;
};

