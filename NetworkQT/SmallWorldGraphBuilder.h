#pragma once
#include "GraphBuilder.h"
class SmallWorldGraphBuilder : public GraphBuilder
{
public:
	SmallWorldGraphBuilder();
	~SmallWorldGraphBuilder();
	std::unique_ptr<HNAGraph> getGraph(const GraphOptions& options)
	{
		int n = options.n_vertices_;
		double b = options.b_;
		int k = options.k_;
		assert(n > 0 && n > k && "ERROR: SmallWorldGraphBuilder: invalid arguments");
		assert(k % 2 == 0 && "ERROR: SmallWorldGraphBuilder: invalid arguments");
		assert(b >= 0 && b <= 1 && "ERROR:SmallWorldGraphBuilder: invalid arguments");

		typedef HNAGraph::Vertex V;

		std::map<V, std::vector<V>> notNeighbors;
		std::vector<V> allVertices(n);
		for (int i = 0; i < n; i++)
		{
			allVertices[i] = i;
		}

		for (int i = 0; i < n; i++)
		{
			notNeighbors[i] = allVertices;
			notNeighbors[i].erase(std::remove(notNeighbors[i].begin(), notNeighbors[i].end(), i), notNeighbors[i].end());
		}

		std::unique_ptr<HNAGraph> gptr(new HNAGraph(n));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int diff1 = abs(i - j);
				int diff2 = abs(n - 1 - k / 2);
				if ((diff1 % diff2) <= k / 2 && (diff1 % diff2) > 0 )
				{
					(*gptr).AddEdge(i, j);
					notNeighbors[i].erase(std::remove(notNeighbors[i].begin(), notNeighbors[i].end(), j), notNeighbors[i].end());
					notNeighbors[j].erase(std::remove(notNeighbors[j].begin(), notNeighbors[j].end(), i), notNeighbors[j].end());
				}
			}
		}
		std::cout << "Edges " << (*gptr).getEdgeCount();
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if ((*gptr).edgeExists(i, j))
				{
					bool rewire = RandomManager::sharedManager()->event(b);
					if (rewire)
					{
						int notNCount = notNeighbors[i].size();
						int randomIndex = RandomManager::sharedManager()->random(0, notNCount - 1);
						int target = notNeighbors[i][randomIndex];
						(*gptr).AddEdge(i, target);
						(*gptr).RemoveEdge(i, j);
						notNeighbors[i].erase(std::remove(notNeighbors[i].begin(), notNeighbors[i].end(), target), notNeighbors[i].end());
						notNeighbors[target].erase(std::remove(notNeighbors[target].begin(), notNeighbors[target].end(), i), notNeighbors[target].end());
						notNeighbors[i].push_back(j);
						notNeighbors[j].push_back(i);
					}
				}
			}
		}
		return gptr;
	}
};

