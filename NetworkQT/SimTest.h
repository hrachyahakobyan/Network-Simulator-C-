#pragma once
#include "BroadcastSimulation.h"

struct TestOptions
{
	int iterCount_;
	TestOptions() : iterCount_(1){};
};

class SimTestCallBack
{
public:
	virtual void testCallback(int it, double t, bool f, std::string filename = "") = 0;
};

class SimTest
{
public:
	SimTest();
	~SimTest();

	bool isRunning_;

	void cancel();
	virtual void test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top, SimTestCallBack* callBack = 0) = 0;
protected:
	template <typename T> double mean(const std::vector<T>& vals) ;
	template <typename T> double var(const std::vector<T>& vals) ;
	template <typename T> T median(std::vector<T> vals) ;
	template <typename T> std::pair<T, T> minmax(const std::vector<T>& vals) ;
	bool isCancelled_;
};

template <typename T>
double SimTest::mean(const std::vector<T>& vals) 
{
	auto it = vals.begin();
	T sum = 0;
	for (; it != vals.end(); ++it)
		sum += *it;
	return double(sum) / vals.size();
}

template <typename T>
double SimTest::var(const std::vector<T>& vals) 
{
	if (vals.size() == 1)
		return 0;
	double m = mean(vals);
	auto it = vals.begin();
	double sum = 0;
	for (; it != vals.end(); ++it)
		sum += std::pow((m - *it), 2);
	return sum / (vals.size() - 1);
}

template <typename T>
T SimTest::median(std::vector<T> vals) 
{
	if (vals.size() == 1)
		return vals[0];
	std::sort(vals.begin(), vals.end());
	int size = vals.size();
	if (size % 2 == 0)
	{
		return T((vals[size / 2 - 1] + vals[size / 2]) / 2);
	}
	else
	{
		return vals[size / 2 + 1];
	}
}

template <typename T>
std::pair<T, T> SimTest::minmax(const std::vector<T>& vals) 
{
	if (vals.size() == 0)
		return std::make_pair ( T{}, T{} ) ;
	std::pair<T, T> mm(vals[0], vals[0]);
	auto it = vals.begin();
	for (; it != vals.end(); ++it)
	{
		if (*it < mm.first)
			mm.first = *it;
		if (*it > mm.second)
			mm.second = *it;
	}
	return mm;
}