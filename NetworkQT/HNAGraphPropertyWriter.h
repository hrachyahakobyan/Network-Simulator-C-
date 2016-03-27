#pragma once
#include <fstream>
#include "HNAGraph.h"


struct HNAGraphPropertyWriterOptions
{
	bool w_type_;
	bool w_nodes_;
	bool w_edges_;
	int font_size_;
	HNAGraphPropertyWriterOptions(bool wt, bool wn, bool we) : w_type_(wt), w_nodes_(wn), w_edges_(we), font_size_(12){};
};

class HNAGraphPropertyWriter
{
public:
	HNAGraphPropertyWriter(const HNAGraphPropertyWriterOptions& options) : options_(options){};
	~HNAGraphPropertyWriter();

	void set_g_prop(const HNAGraphBundle& g_prop)
	{
		g_prop_ = g_prop;
	}

	void operator () (std::ostream& os) const
	{
		if (options_.w_edges_ == false && options_.w_edges_ == false && options_.w_type_ == false)
			return;
		os << "label = \"";
		std::string title;
		if (options_.w_type_ == true)
		{
			title.append("Type ");
			title.append(g_prop_.type_);
			title.append("\n");
		}
		if (options_.w_edges_)
		{
			title.append("Edges ");
			title.append(std::to_string(n_edges_));
			title.append("\n");
		}
		if (options_.w_nodes_)
		{
			title.append("Nodes ");
			title.append(std::to_string(n_vertices_));
			title.append("\n");
		}
		title.append("Broadcasting ");
		title.append(g_prop_.broadcast_type_);
		title.append("\n");
		title.append("Broadcast time ");
		title.append(std::to_string(g_prop_.broadcast_time_));
		title.append("\n");
		title.append("\"");
		os << title;

		os << "fontsize=";
		os << std::to_string(options_.font_size_);
		os << "\n";

		os << "\n";
	}

	int& edges()
	{
		return n_edges_;
	}

	int& vertices()
	{
		return n_vertices_;
	}
private:
	HNAGraphPropertyWriterOptions options_;
	HNAGraphBundle g_prop_;
	int n_edges_;
	int n_vertices_;
};

