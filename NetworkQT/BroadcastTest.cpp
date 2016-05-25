#include "stdafx.h"
#include "BroadcastTest.h"


BroadcastTest::BroadcastTest()
{
}


BroadcastTest::~BroadcastTest()
{
}



void BroadcastTest::test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top, Progress_F f)
{
	isCancelled_ = false;
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
		qDebug() << "Iteration " << j << "\n";
		if (isCancelled_)
		{
			qDebug() << "Cancelled, finishing test\n";
			isCancelled_ = false;
			return;
		}
		int randomOriginator = RandomManager::sharedManager()->random(0, (*sim_ptr).vertexCount() - 1);
		editAction.v_ = randomOriginator;
		(*sim_ptr).edit(editAction);
		(*sim_ptr).finish();
		int bTime = (*sim_ptr).broadcastTime();
		bTimes[j] = bTime;
		(*sim_ptr).reset();
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
}