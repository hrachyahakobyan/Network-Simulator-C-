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
		enum class Sex{Male, Female};
		Sex sex_;
		std::string label_;
		int state_;
		std::set<int> informers_;
		int inf_preiod_;
		int imm_period_;
		HNANodeBundle() : state_(0), sex_(Sex::Male){};
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
	HNAGraph();
	HNAGraph(int v);
	HNAGraph(const HNAGraph& g);
	~HNAGraph();
	/* operators */
	HNAGraph& operator=(const HNAGraph &rhs);
	HNAGraph& operator+=(const HNAGraph& rhs);

	void attach(const HNAGraph& other, const Vertex& originV, const Vertex& otherV);
	void clear();
	Vertex add_vertex();
	void remove_vertex(const Vertex& v);
	std::pair<Edge, bool> add_edge(const Vertex& v1, const Vertex& v2);
	void remove_edge(const Vertex& v1, const Vertex& v2);
	void remove_edge(const Edge& e);
	HNANodeBundle& properties(const Vertex& v);
	const HNANodeBundle& properties(const Vertex& v) const;
	HNAEdgeBundle& properties(const Edge& v);
	const HNAEdgeBundle& properties(const Edge& v) const;
	HNAGraphBundle& properties();
	const HNAGraphBundle& properties() const;
	const Index_Map& i_map() const;
	Degree_Map deg_map() const;
	int deg_sum() const;
	Const_Vertex_Params v_params() const;
	const GraphContainer& graph() const;
	Vertex_Range vertices() const;
	std::set<Vertex> vertices_set() const;
	std::vector<Vertex> vertices_vector() const;
	Adjacency_Range adjacent_vertices(const Vertex& v) const;
	int vertex_count() const;
	int vertex_degree(const Vertex& v) const;
	int edge_count() const;
	void print_vertex(const Vertex& v) const;
	void print_graph() const;
	bool vertex_exists(const Vertex& v);
	bool edge_exists(const Vertex& v1, const Vertex& v2);

private:
	GraphContainer g_container;
};


//HNAGraph operator+(const HNAGraph &g1, const HNAGraph &g2)
//{
//	HNAGraph result(g1);
//	result += g2;
//	return result;
//}