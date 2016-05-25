#include "stdafx.h"
#include "BroadcastTest.h"


BroadcastTest::BroadcastTest()
{
}


BroadcastTest::~BroadcastTest()
{
}



void BroadcastTest::test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top, SimTestCallBack* callback)
{
	isCancelled_ = false;
	isRunning_ = true;

	double totalTime = 0;

	typedef boost::filesystem::path Path;
	Path folderPath = FileManager::sharedManager()->stat_path();
	int iterCount = top.iterCount_;
	GraphEditAction editAction;
	editAction.type_ = GraphEditAction::EditType::SetState;
	editAction.state_ = Two_State::informed;

	std::unique_ptr<BroadcastSimulation> sim_ptr = BroadcastSimulation::simulation(gop, sop);
	std::vector<int> bTimes(iterCount);
	int edgeCount = (*sim_ptr).edgeCount();
	for (int j = 0; j < iterCount; j++)
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		qDebug() << "Iteration " << j << "\n";
		if (isCancelled_)
		{
			qDebug() << "Cancelled, finishing test\n";
			isCancelled_ = false;
			isRunning_ = false;
			if (callback)
				callback->testCallback(j + 1, 0, true);
			return;
		}
		int randomOriginator = RandomManager::sharedManager()->random(0, (*sim_ptr).vertexCount() - 1);
		editAction.v_ = randomOriginator;
		(*sim_ptr).edit(editAction);
		(*sim_ptr).finish();
		int bTime = (*sim_ptr).broadcastTime();
		bTimes[j] = bTime;
		(*sim_ptr).reset();
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		double iterDur = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		totalTime += iterDur;
		double estimate = double(iterCount - j - 1) / (j + 1) * totalTime;
		if (callback)
			callback->testCallback(j + 1, estimate, false);
	}

		/*Write the results*/
		double averageBT = mean(bTimes);
		double varBT = var(bTimes);
		int medianBT = median(bTimes);

		std::pair<int, int> mm = minmax<int>(bTimes);
		std::string filename(folderPath.string());
		filename.append("/stat");
		filename.append(".txt");
		std::ofstream file;
		file.open(filename);

		file << "Graph type " << gop.graphType() << "\n";
		file << "Vertex count  = " << (*sim_ptr).vertexCount() << "\n";
		file << "Edge count = " << (*sim_ptr).edgeCount() << "\n";
		file << "Iteration count " << iterCount << "\n";
		file << "\n \n";
		file << "Broadcast type = " << sop.send_type_ << "\n";
		file << "\n \n";
		file << "Lower bound " << int(ceil(std::log2(gop.n_vertices_))) << "\n";
		file << "Minimum broadcast time " << mm.first << "\n";
		file << "Maximum broadcast time " << mm.second << "\n";
		file << "Average broadcast time " << averageBT << "\n";
		file << "Variance broadcast time " << varBT << "\n";
		file << "Median brodcast time " << medianBT << "\n";
		file << "\n \n";
		file.close();
		isRunning_ = false;
		if (callback)
			callback->testCallback(iterCount, 0, true, folderPath.string());
}