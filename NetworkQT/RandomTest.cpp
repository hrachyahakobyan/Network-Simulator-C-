#include "stdafx.h"
#include "RandomTest.h"


RandomTest::RandomTest()
{
}


RandomTest::~RandomTest()
{
}

void RandomTest::test(const GraphBuilder::GraphOptions& gop, const BroadcastSchemeOptions& sop, const TestOptions& top)
{
	typedef boost::filesystem::path Path;
	Path folderPath = FileManager::sharedManager()->stat_path();

	int graphCount = top.graphCount_;
	int iterCount = top.iterCount_;
	GraphEditAction editAction;
	editAction.type_ = GraphEditAction::EditType::SetState;
	editAction.state_ = Two_State::informed;

	std::vector<double> averageBTimes(graphCount);
	std::vector<int> minBTimes(graphCount);
	std::vector<int> maxBTimes(graphCount);
	int edgeCount = 0;


	for (int i = 0; i < graphCount; i++)
	{
		std::unique_ptr<BroadcastSimulation> sim_ptr = BroadcastSimulation::simulation(gop, sop);
		std::vector<int> bTimes(iterCount);
		edgeCount = (*sim_ptr).edgeCount();
		for (int j = 0; j < iterCount; j++)
		{
			qDebug() << "Graph " << i << " Iteration " << j << "\n";
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

		averageBTimes[i] = averageBT;
		minBTimes[i] = mm.first;
		maxBTimes[i] = mm.second;

		std::string filename(folderPath.string());
		filename.append("/stat");
		filename.append(std::to_string(i));
		filename.append(".txt");
		std::ofstream file;
		file.open(filename);

		file << "Graph type = Erdos-Reniy Random graph \n";
		file << "Param N = " << gop.n_vertices_ << ", Prob = " << gop.p_ << "\n";
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

	if (graphCount == 1)
		return;

	double averageOfAverage = mean(averageBTimes);
	double varAverage = var(averageBTimes);
	double medianAverage = median(averageBTimes);

	double averageMax = mean(maxBTimes);
	double varMax = var(maxBTimes);
	int medianMax = median(maxBTimes);

	double averageMin = mean(minBTimes);
	double varMin = var(minBTimes);
	int medianMin = median(minBTimes);

	int globMin = minmax<int>(minBTimes).first;
	int globMax = minmax<int>(maxBTimes).second;

	std::string finalFileName(folderPath.string());
	finalFileName.append("/stat.txt");
	std::ofstream file;
	file.open(finalFileName);
	file << "Graph type = Erdos-Reniy Random graph \n";
	file << "Param N = " << gop.n_vertices_ << ", Prob = " << gop.p_ << "\n";
	file << "Vertex count " << gop.n_vertices_ << "\n";
	file << "Edge count " << edgeCount << "\n";
	file << "Broadcast Time " << sop.send_type_ << "\n";
	file << "Graph iteration count " << graphCount << "\n";
	file << "Originator iteration count " << iterCount << "\n";
	file << "\n \n \n";
	file << "Global minimum " << globMin << "\n";
	file << "GLobal maximum " << globMax << "\n";
	file << "Average of Average broadcast times " << averageOfAverage << "\n";
	file << "Variance of average broadcast times " << varAverage << "\n";
	file << "Median of average broadcast times " << medianAverage << "\n";
	file << "\n";
	file << "Average of maximum broadcast times " << averageMax << "\n";
	file << "Variance of maximum broadcast times " << varMax << "\n";
	file << "Median of maximum broadcast times " << medianMax << "\n";
	file << "\n";
	file << "Average of minimum broadcast times " << averageMin << "\n";
	file << "Variance of minimum broadcast times " << varMin << "\n";
	file << "Median of minimum broadcast times " << medianMin << "\n";
	file.close();
}