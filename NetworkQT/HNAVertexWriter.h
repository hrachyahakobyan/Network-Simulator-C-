#pragma once
#include <fstream>
#include "Constants.h"
#include "HNAGraph.h"

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

	void operator()(std::ostream &out, const HNAGraph::Vertex& v) const
	{
		if (options_.write_labels_ == false && options_.write_colors_ == false)
			return;
		out << "[";
		if (options_.write_labels_ == true)
		{
			out << "label=\"" << v_params_[v].label_ << "\", ";
		}
		if (options_.write_colors_ == true)
		{
			if (v_params_[v].state_ > - 1)
				out << "style=filled, " << "fillcolor=\"" << color_map_.at(v_params_[v].state_) << "\", fontcolor=\"" << font_color_map_.at(color_map_.at(v_params_[v].state_)) << "\"";
		}
		out << "]";
	}

private:
	HNAVertexWriteOptions options_;
	HNAGraph::Const_Vertex_Params v_params_;
	std::map<int, std::string> color_map_;
	std::map<std::string, std::string> font_color_map_;
};

