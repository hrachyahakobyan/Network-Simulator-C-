#include "stdafx.h"
#include "HNAGraph.h"


HNAGraph::HNAGraph()
{
}

HNAGraph::HNAGraph(int v) : g_container(v)
{
}

HNAGraph::HNAGraph(const HNAGraph& g) :
g_container(g.g_container)
{
}

HNAGraph::~HNAGraph()
{
}

HNAGraph& HNAGraph::operator=(const HNAGraph &rhs)
{
	g_container = rhs.g_container;
	return *this;
}

HNAGraph& HNAGraph::operator+=(const HNAGraph& rhs)
{
	boost::copy_graph(rhs.g_container, this->g_container);
	return *this;
}

void HNAGraph::attach(const HNAGraph& other, const Vertex& originV, const Vertex& otherV)
{
	int v_count = this->vertex_count();
	*this += other;
	add_edge(originV, otherV + v_count);
}

void HNAGraph::clear()
{
	g_container.clear();
}

HNAGraph::Vertex HNAGraph::add_vertex()
{
	Vertex v = boost::add_vertex(g_container);
	return v;
}

void HNAGraph::remove_vertex(const Vertex& v)
{
	if (v + 1 <= num_vertices(g_container))
	{
		boost::clear_vertex(v, g_container);
		boost::remove_vertex(v, g_container);
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

std::pair<HNAGraph::Edge, bool> HNAGraph::add_edge(const Vertex& v1, const Vertex& v2)
{
	if (vertex_exists(v1) && vertex_exists(v2) && v1 != v2)
	{
		std::pair<Edge, bool> pair = boost::add_edge(v1, v2, g_container);
		return pair;
	}
	return std::pair<Edge, bool>(Edge(), false);
}

void HNAGraph::remove_edge(const Vertex& v1, const Vertex& v2)
{
	std::pair<Edge, bool> pair = edge(v1, v2, g_container);
	if (pair.second == true)
		remove_edge(pair.first);
}

void HNAGraph::remove_edge(const Edge& e)
{
	g_container.remove_edge(e);
}
/* property access */

HNAGraph::HNANodeBundle& HNAGraph::properties(const Vertex& v)
{
	boost::property_map<GraphContainer, vertex_properties_t>::type param = get(vertex_properties, g_container);
	return param[v];
}

const HNAGraph::HNANodeBundle& HNAGraph::properties(const Vertex& v) const
{
	boost::property_map<GraphContainer, vertex_properties_t>::const_type param = get(vertex_properties, g_container);
	return param[v];
}

HNAGraph::HNAEdgeBundle& HNAGraph::properties(const Edge& v)
{
	boost::property_map<GraphContainer, edge_properties_t>::type param = get(edge_properties, g_container);
	return param[v];
}

const HNAGraph::HNAEdgeBundle& HNAGraph::properties(const Edge& v) const
{
	boost::property_map<GraphContainer, edge_properties_t>::const_type param = get(edge_properties, g_container);
	return param[v];
}

HNAGraph::HNAGraphBundle& HNAGraph::properties()
{
	return g_container[boost::graph_bundle];
}

const HNAGraph::HNAGraphBundle& HNAGraph::properties() const
{
	return g_container[boost::graph_bundle];
}

const HNAGraph::Index_Map& HNAGraph::i_map() const
{
	return get(boost::vertex_index, g_container);
}

HNAGraph::Degree_Map HNAGraph::deg_map() const
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

int HNAGraph::deg_sum() const
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

HNAGraph::Const_Vertex_Params HNAGraph::v_params() const
{
	return get(vertex_properties, g_container);
}

/* selectors and properties */

const HNAGraph::GraphContainer& HNAGraph::graph() const
{
	return g_container;
}

HNAGraph::Vertex_Range HNAGraph::vertices() const
{
	return boost::vertices(g_container);
}

std::set<HNAGraph::Vertex> HNAGraph::vertices_set() const
{
	std::set<Vertex> set;
	Vertex_Range vp = vertices();
	for (vp; vp.first != vp.second; ++vp.first)
	{
		set.insert(*vp.first);
	}
	return set;
}

std::vector<HNAGraph::Vertex> HNAGraph::vertices_vector() const
{
	std::vector<Vertex> vec;
	Vertex_Range vp = vertices();
	for (vp; vp.first != vp.second; ++vp.first)
	{
		vec.push_back(*vp.first);
	}
	return vec;
}

HNAGraph::Adjacency_Range HNAGraph::adjacent_vertices(const Vertex& v) const
{
	return boost::adjacent_vertices(v, g_container);
}

int HNAGraph::vertex_count() const
{
	return num_vertices(g_container);
}

int HNAGraph::vertex_degree(const Vertex& v) const
{
	return out_degree(v, g_container);
}

int HNAGraph::edge_count() const
{
	return num_edges(g_container);
}


void HNAGraph::print_vertex(const Vertex& v) const
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
	for (boost::tie(ai, ai_end) = adjacent_vertices(v);
		ai != ai_end; ++ai)
		std::cout << graph_indeces[*ai] << " ";
	std::cout << std::endl;
}

void HNAGraph::print_graph() const
{
	std::cout << "Printing graph \n \n";
	std::cout << "Vertex indeces \n \n";
	std::pair<Vertex_Iter, Vertex_Iter> vp;
	Index_Map graph_indeces = get(boost::vertex_index, g_container);
	for (vp = boost::vertices(g_container); vp.first != vp.second; ++vp.first)
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
	for (vp = boost::vertices(g_container); vp.first != vp.second; ++vp.first)
	{
		print_vertex(*vp.first);
	}

}

bool HNAGraph::vertex_exists(const HNAGraph::Vertex& v)
{
	std::pair<Vertex_Iter, Vertex_Iter> vp;
	Index_Map graph_indeces = boost::get(boost::vertex_index, g_container);
	for (vp = boost::vertices(g_container); vp.first != vp.second; ++vp.first)
	{
		if (graph_indeces[*vp.first] == graph_indeces[v])
		{
			return true;
		}
	}
	return false;
}

bool HNAGraph::edge_exists(const Vertex& v1, const Vertex& v2)
{
	return boost::edge(v1, v2, g_container).second;
}


