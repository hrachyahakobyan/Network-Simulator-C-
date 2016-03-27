#pragma once

enum vertex_properties_t { vertex_properties };
enum edge_properties_t { edge_properties };

namespace boost
{
	BOOST_INSTALL_PROPERTY(vertex, properties);
	BOOST_INSTALL_PROPERTY(edge, properties);
}

struct HNANodeBundle
{
	std::string label_;
	int state_;
	std::set<int> informers_;
	HNANodeBundle() : state_(0){};
};

struct HNAEdgeBundle
{

};

struct HNAGraphBundle
{
	std::string type_;
	std::string broadcast_type_;
	int broadcast_time_;
	HNAGraphBundle() : broadcast_time_(0){};
};

using namespace boost;

typedef adjacency_list<setS, vecS, undirectedS,
	property<vertex_properties_t, HNANodeBundle>,
	property<edge_properties_t, HNAEdgeBundle>,
	HNAGraphBundle
> GraphContainer;

typedef  graph_traits<GraphContainer>::vertex_descriptor Vertex;
typedef  graph_traits<GraphContainer>::edge_descriptor Edge;

typedef  graph_traits<GraphContainer>::vertex_iterator vertex_iter;
typedef  graph_traits<GraphContainer>::edge_iterator edge_iter;
typedef  graph_traits<GraphContainer>::adjacency_iterator adjacency_iter;
typedef  graph_traits<GraphContainer>::out_edge_iterator out_edge_iter;
typedef  graph_traits<GraphContainer>::degree_size_type degree_t;
typedef  property_map<GraphContainer, vertex_index_t>::type index_map;
typedef  property_map<GraphContainer, vertex_properties_t>::const_type vertex_params;
typedef std::pair<adjacency_iter, adjacency_iter> adjacency_vertex_range_t;
typedef std::pair<out_edge_iter, out_edge_iter> out_edge_range_t;
typedef std::pair<vertex_iter, vertex_iter> vertex_range_t;
typedef std::pair<edge_iter, edge_iter> edge_range_t;

class HNAGraph
{
public:

	friend class HypercubeBuilder;
	friend class CompleteGraphBuilder;
	friend class HNAGraphWriter;
	friend class BroadcastSimulation;
	
	/*Constructors and destructor*/
	HNAGraph()
	{}

	HNAGraph(int v) : g_container(v)
	{}

	HNAGraph(const HNAGraph& g) :
		g_container(g.g_container)
	{}

	virtual ~HNAGraph()
	{
	}

	friend HNAGraph operator+(const HNAGraph &g1, const HNAGraph &g2)
	{
		HNAGraph result(g1);
		result += g2;
		return result;
	}

	HNAGraph& operator+=(const HNAGraph& rhs) 
	{
		copy_graph(rhs.g_container, this->g_container);
		return *this; // return the result by reference
	}

	void Attach(const HNAGraph& other, const Vertex& originV, const Vertex& otherV)
	{
		int v_count = this->getVertexCount();
		*this += other;
		AddEdge(originV, otherV + v_count);
	}

	void Clear()
	{
		g_container.clear();
	}
	
	Vertex AddVertex()
	{
		Vertex v = add_vertex(g_container);
		return v;
	}

	void RemoveVertex(const Vertex& v)
	{
		if (v + 1 <= num_vertices(g_container))
		{
			clear_vertex(v, g_container);
			remove_vertex(v, g_container);
			vertex_range_t vers = vertices(g_container);
			for (; vers.first != vers.second; ++vers.first)
			{
				std::set<int>::iterator it;
				std::set<int> new_set;
				for (it = properties(*vers.first).informers_.begin(); it != properties(*vers.first).informers_.end(); ++it)
				{
					if (unsigned(*it) < v)
						new_set.insert(*it);
					else if (unsigned(*it) > v)
						new_set.insert(*it - 1);
				}
				properties(*vers.first).informers_.clear();
				properties(*vers.first).informers_.insert(new_set.begin(), new_set.end());
			}
		}
	}

	std::pair<Edge, bool> AddEdge(const Vertex& v1, const Vertex& v2)
	{
		if (vertexExists(v1) && vertexExists(v2))
		{
			std::pair<Edge, bool> pair =  add_edge(v1, v2, g_container);
			return pair;
		}
		return std::pair<Edge, bool>(Edge(), false);
	}

	void RemoveEdge(const Vertex& v1, const Vertex& v2)
	{
		std::pair<Edge, bool> pair = edge(v1, v2, g_container);
		if (pair.second == true)
			RemoveEdge(pair.first);
	}

	void RemoveEdge(const Edge& e)
	{
		g_container.remove_edge(e);
	}
	/* property access */
	
	HNANodeBundle& properties(const Vertex& v)
	{
		property_map<GraphContainer, vertex_properties_t>::type param = get(vertex_properties, g_container);
		return param[v];
	}

	const HNANodeBundle& properties(const Vertex& v) const
	{
		property_map<GraphContainer, vertex_properties_t>::const_type param = get(vertex_properties, g_container);
		return param[v];
	}

	HNAEdgeBundle& properties(const Edge& v)
	{
		property_map<GraphContainer, edge_properties_t>::type param = get(edge_properties, g_container);
		return param[v];
	}

	const HNAEdgeBundle& properties(const Edge& v) const
	{
		property_map<GraphContainer, edge_properties_t>::const_type param = get(edge_properties, g_container);
		return param[v];
	}

	HNAGraphBundle& properties()
	{
		return g_container[graph_bundle];
	}

	const HNAGraphBundle& properties() const
	{
		return g_container[graph_bundle];
	}

	const index_map& i_map() const
	{
		return get(vertex_index, g_container);
	}


	vertex_params v_params() const
	{
		return get(vertex_properties, g_container);
	}

	/* selectors and properties */
	
	const GraphContainer& getGraph() const
	{
		return g_container;
	}

	vertex_range_t getVertices() const
	{
		return vertices(g_container);
	}

	adjacency_vertex_range_t getAdjacentVertices(const Vertex& v) const
	{
		return adjacent_vertices(v, g_container);
	}

	int getVertexCount() const
	{
		return num_vertices(g_container);
	}

	int getVertexDegree(const Vertex& v) const
	{
		return out_degree(v, g_container);
	}

	int getEdgeCount() const
	{
		return num_edges(g_container);
	}


	void printVertex(const Vertex& v) const
	{
		std::cout << std::endl;
		index_map graph_indeces = get(vertex_index, g_container);
		std::cout << "Printing vertex " << graph_indeces[v] << " label " << properties(v).label_ << " state " << properties(v).state_ << std::endl;
		std::cout << "\n";
		std::cout << "Out-edges: ";
		out_edge_iter out_i, out_end;
		for (boost::tie(out_i, out_end) = out_edges(v, g_container); out_i != out_end; ++out_i)
		{
			Vertex src = source(*out_i, g_container), targ = target(*out_i, g_container);
			std::cout << "(" << graph_indeces[src] << "," << graph_indeces[targ] << ")";
		}

		std::cout << "Informers " << std::endl;
		std::set<int>::iterator inf_it;
		for (inf_it = properties(v).informers_.begin(); inf_it != properties(v).informers_.end(); ++inf_it)
		{
			std::cout << *inf_it << " ";
		}

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "adjacent vertices: ";
		adjacency_iter ai, ai_end;
		for (boost::tie(ai, ai_end) = getAdjacentVertices(v);
			ai != ai_end; ++ai)
			std::cout << graph_indeces[*ai] << " ";
		std::cout << std::endl;
	}

	void printGraph() const
	{
		std::cout << "Printing graph \n \n";
		std::cout << "Vertex indeces \n \n";
		std::pair<vertex_iter, vertex_iter> vp;
		index_map graph_indeces = get(vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			std::cout << graph_indeces[*vp.first] << " ";
		}
		std::cout << "Edges \n \n";
		edge_iter ei, ei_end;
		for (boost::tie(ei, ei_end) = edges(g_container); ei != ei_end; ++ei)
		{
			std::cout << source(*ei, g_container) << "-" << target(*ei, g_container);
		}
		std::cout << std::endl;
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			printVertex(*vp.first);
		}
		
	}

	std::pair<const Vertex&, bool> getVertexAtIndex(vertex_index_t index) const
	{
		std::pair<vertex_iter, vertex_iter> vp;
		index_map graph_indeces = get(vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			if (graph_indeces[*vp.first] == index)
			{
				return std::pair<const Vertex&, bool>(*vp.first, true);
			}
		}
		return std::pair<const Vertex&, bool>(Vertex(), false);
	}

	bool vertexExistsAtIndex(vertex_index_t index)
	{
		return getVertexAtIndex(index).second;
	}

	bool vertexExists(const Vertex& v)
	{
		std::pair<vertex_iter, vertex_iter> vp;
		index_map graph_indeces = get(vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			if (graph_indeces[*vp.first] == graph_indeces[v])
			{
				return true;
			}
		}
		return false;
	}

	/* operators */
	HNAGraph& operator=(const HNAGraph &rhs)
	{
		g_container = rhs.g_container;
		return *this;
	}

private:
	GraphContainer g_container;
};

