#pragma once

enum vertex_properties_t { vertex_properties };
enum edge_properties_t { edge_properties };

namespace boost
{
	BOOST_INSTALL_PROPERTY(vertex, properties);
	BOOST_INSTALL_PROPERTY(edge, properties);
}

class HNAGraph
{
	/* Bundles */
public:
	struct HNANodeBundle
	{
		std::string label_;
		int state_;
		std::set<int> informers_;
		
		int inf_preiod_;
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
public:
	/*Typedefs*/
	typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,
		boost::property<vertex_properties_t, HNANodeBundle>,
		boost::property<edge_properties_t, HNAEdgeBundle>,
		HNAGraphBundle
	> GraphContainer;
	typedef  boost::graph_traits<GraphContainer>::vertex_descriptor Vertex;
	typedef  boost::graph_traits<GraphContainer>::edge_descriptor Edge;
	typedef  boost::graph_traits<GraphContainer>::vertex_iterator Vertex_Iter;
	typedef  boost::graph_traits<GraphContainer>::edge_iterator Edge_Iter;
	typedef  boost::graph_traits<GraphContainer>::adjacency_iterator Adjacency_Iter;
	typedef  boost::graph_traits<GraphContainer>::out_edge_iterator Out_Edge_Iter;
	typedef  boost::graph_traits<GraphContainer>::degree_size_type Degree_T;
	typedef  boost::property_map<GraphContainer, boost::vertex_index_t>::type Index_Map;
	typedef  boost::property_map<GraphContainer, vertex_properties_t>::const_type Const_Vertex_Params;
	typedef std::pair<Adjacency_Iter, Adjacency_Iter> Adjacency_Range;
	typedef std::pair<Out_Edge_Iter, Out_Edge_Iter> Out_Edge_Range;
	typedef std::pair<Vertex_Iter, Vertex_Iter> Vertex_Range;
	typedef std::pair<Edge_Iter, Edge_Iter> Edge_Range;
	typedef std::map<Vertex, int> Degree_Map;

public:

	friend class HypercubeBuilder;
	friend class CompleteGraphBuilder;
	friend class HNAGraphWriter;
	friend class BroadcastSimulation;
	friend class RandomGraphBuilder;
	friend class CustomGraphBuilder;
	/*Constructors and destructor*/
	HNAGraph()
	{}

	HNAGraph(int v) : g_container(v)
	{}

	HNAGraph(const HNAGraph& g) :
		g_container(g.g_container)
	{
		std::cout << "Copy constructor \n";
	}

	/* operators */
	HNAGraph& operator=(const HNAGraph &rhs)
	{
		g_container = rhs.g_container;
		std::cout << "Copy assignment \n";
		return *this;
	}

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
		boost::copy_graph(rhs.g_container, this->g_container);
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
			Vertex_Range vers = boost::vertices(g_container);
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
		if (vertexExists(v1) && vertexExists(v2) && v1 != v2)
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
		boost::property_map<GraphContainer, vertex_properties_t>::type param = get(vertex_properties, g_container);
		return param[v];
	}

	const HNANodeBundle& properties(const Vertex& v) const
	{
		boost::property_map<GraphContainer, vertex_properties_t>::const_type param = get(vertex_properties, g_container);
		return param[v];
	}

	HNAEdgeBundle& properties(const Edge& v)
	{
		boost::property_map<GraphContainer, edge_properties_t>::type param = get(edge_properties, g_container);
		return param[v];
	}

	const HNAEdgeBundle& properties(const Edge& v) const
	{
		boost::property_map<GraphContainer, edge_properties_t>::const_type param = get(edge_properties, g_container);
		return param[v];
	}

	HNAGraphBundle& properties()
	{
		return g_container[boost::graph_bundle];
	}

	const HNAGraphBundle& properties() const
	{
		return g_container[boost::graph_bundle];
	}

	const Index_Map& i_map() const
	{
		return get(boost::vertex_index, g_container);
	}

	Degree_Map deg_map() const
	{
		Degree_Map map;
		Vertex_Range vp = boost::vertices(g_container);
		boost::degree_property_map<GraphContainer> d = boost::make_degree_map(g_container);
		for (; vp.first != vp.second; ++vp.first)
		{
			map.insert(std::make_pair(*vp.first, d[*vp.first]));
		}
		return map;
	}

	int deg_sum() const
	{
		int sum = 0;
		Vertex_Range vp = boost::vertices(g_container);
		boost::degree_property_map<GraphContainer> d = boost::make_degree_map(g_container);
		for (; vp.first != vp.second; ++vp.first)
		{
			sum += d[*vp.first];
		}
		return sum;
	}

	Const_Vertex_Params v_params() const
	{
		return get(vertex_properties, g_container);
	}

	/* selectors and properties */
	
	const GraphContainer& getGraph() const
	{
		return g_container;
	}

	Vertex_Range getVertices() const
	{
		return vertices(g_container);
	}

	std::set<Vertex> getVerticesSet() const
	{
		std::set<Vertex> set;
		Vertex_Range vp = getVertices();
		for (vp; vp.first != vp.second; ++vp.first)
		{
			set.insert(*vp.first);
		}
		return set;
	}

	std::vector<Vertex> getVerticesVector() const
	{
		std::vector<Vertex> vec;
		Vertex_Range vp = getVertices();
		for (vp; vp.first != vp.second; ++vp.first)
		{
			vec.push_back(*vp.first);
		}
		return vec;
	}

	Adjacency_Range getAdjacentVertices(const Vertex& v) const
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
		Index_Map graph_indeces = get(boost::vertex_index, g_container);
		std::cout << "Printing vertex " << graph_indeces[v] << " label " << properties(v).label_ << " state " << properties(v).state_ << std::endl;
		std::cout << "\n";
		std::cout << "Out-edges: ";
		Out_Edge_Iter out_i, out_end;
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
		Adjacency_Iter ai, ai_end;
		for (boost::tie(ai, ai_end) = getAdjacentVertices(v);
			ai != ai_end; ++ai)
			std::cout << graph_indeces[*ai] << " ";
		std::cout << std::endl;
	}

	void printGraph() const
	{
		std::cout << "Printing graph \n \n";
		std::cout << "Vertex indeces \n \n";
		std::pair<Vertex_Iter, Vertex_Iter> vp;
		Index_Map graph_indeces = get(boost::vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			std::cout << graph_indeces[*vp.first] << " ";
		}
		std::cout << "Edges \n \n";
		Edge_Iter ei, ei_end;
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

	std::pair<const Vertex&, bool> getVertexAtIndex(boost::vertex_index_t index) const
	{
		std::pair<Vertex_Iter, Vertex_Iter> vp;
		Index_Map graph_indeces = get(boost::vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			if (graph_indeces[*vp.first] == index)
			{
				return std::pair<const Vertex&, bool>(*vp.first, true);
			}
		}
		return std::pair<const Vertex&, bool>(Vertex(), false);
	}

	bool vertexExistsAtIndex(boost::vertex_index_t index)
	{
		return getVertexAtIndex(index).second;
	}

	bool vertexExists(const Vertex& v)
	{
		std::pair<Vertex_Iter, Vertex_Iter> vp;
		Index_Map graph_indeces = get(boost::vertex_index, g_container);
		for (vp = vertices(g_container); vp.first != vp.second; ++vp.first)
		{
			if (graph_indeces[*vp.first] == graph_indeces[v])
			{
				return true;
			}
		}
		return false;
	}



private:
	GraphContainer g_container;
};

