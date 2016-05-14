#pragma once
#include <fstream>

#define MIN_NODE_SIZE 0.4
#define EXTRA_NODE_SIZE 0.4

struct HNAVertexWriteOptions
{
	bool write_labels_;
	bool write_colors_;
	HNAVertexWriteOptions(bool wl, bool wc) : write_labels_(wl), write_colors_(wc){};
	static HNAVertexWriteOptions defaultOptions()
	{
		return HNAVertexWriteOptions(false, true);
	}
};

class HNAVertexWriter
{
public:
	HNAVertexWriter(const HNAVertexWriteOptions& options) : options_(options), color_map_(DEFAULT_COLOR_MAP)
	{
		font_color_map_.insert(std::make_pair("white", "black"));
		font_color_map_.insert(std::make_pair("black", "white"));
		font_color_map_.insert(std::make_pair("blue", "white"));
		font_color_map_.insert(std::make_pair("red", "white"));
		font_color_map_.insert(std::make_pair("green", "white"));
	};

	static HNAVertexWriter defaultWriter()
	{
		return HNAVertexWriter(HNAVertexWriteOptions::defaultOptions());
	}
	~HNAVertexWriter(){};

	void set_color_map(const std::map<int, std::string>& color_map) 
	{
		color_map_ = color_map;
	}

	void set_v_prop(const HNAGraph::Const_Vertex_Params& v_params)
	{
		v_params_ = v_params;
	}

	void set_deg_map(const HNAGraph::Degree_Map& deg_map)
	{
		deg_map_ = deg_map;
		getMinMax();
	}

	void operator()(std::ostream &out, const HNAGraph::Vertex& v) const
	{
		out << "[shape=";
		if (v_params_[v].sex_ == HNAGraph::HNANodeBundle::Sex::Male)
		{
			out << "circle";
		}
		else
		{
			out << "doublecircle";
		}
		if (options_.write_labels_ == true)
		{
			out << ",label=\"" << v_params_[v].label_ << "\" ";
		}
		if (options_.write_colors_ == true)
		{
			if (v_params_[v].state_ > - 1)
				out << ",style=filled, " << "fillcolor=\"" << color_map_.at(v_params_[v].state_) << "\", fontcolor=\"" << font_color_map_.at(color_map_.at(v_params_[v].state_)) << "\"";
		}
		else
		{
			out << ", style=filled, fillcolor=white";
		}
		if (deg_map_.empty() == false)
		{
			double size = MIN_NODE_SIZE + EXTRA_NODE_SIZE * double(deg_map_.at(v)) / (minmax_.second > 0 ? minmax_.second : 1);
			out << ", width=" << std::to_string(size);
		}
		out << "]";
	}


private:
	HNAVertexWriteOptions options_;
	HNAGraph::Const_Vertex_Params v_params_;
	HNAGraph::Degree_Map deg_map_;
	std::pair<int, int> minmax_;
	std::map<int, std::string> color_map_;
	std::map<std::string, std::string> font_color_map_;
	void getMinMax()
	{
		int min = INT_MAX;
		int max = -1;
		std::map<HNAGraph::Vertex, int>::iterator it;
		for (it = deg_map_.begin(); it != deg_map_.end(); ++it)
		{
			if ((*it).second > max)
				max = (*it).second;
			if ((*it).second < min)
				min = (*it).second;
		}
		minmax_.first = min;
		minmax_.second = max;
	}
};

