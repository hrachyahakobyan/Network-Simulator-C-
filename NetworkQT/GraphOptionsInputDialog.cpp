#include "stdafx.h"
#include "GraphOptionsInputDialog.h"

GraphOptionsInputDialog::GraphOptionsInputDialog(QWidget *parent, QList<QString> labels, const std::string& type)
	: MultiInputDialog(parent, labels), type_(type)
{
	for each (QLineEdit* line in lines_)
	{
		line->setValidator(new QIntValidator(1, 200, this));
	}
}

GraphOptionsInputDialog::~GraphOptionsInputDialog()
{

}

bool GraphOptionsInputDialog::validate()
{
	if (type_.compare(GRAPH_BINOMIAL) == 0)
	{
		assert(inputs_map_.find("Height") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString h_string = inputs_map_["Height"];
		bool b_h;
		int height = h_string.toInt(&b_h);
		if (b_h)
		{
			if (height > 0 && height <= GRAPH_BINOMIAL_MAX_HEIGHT)
				return true;
			return false;
		}
		return false;
	}
	else if (type_.compare(GRAPH_COMPLETE) == 0)
	{
		assert(inputs_map_.find("Vertices") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString v_string = inputs_map_["Vertices"];
		bool b_v;
		int vertices = v_string.toInt(&b_v);
		if (b_v)
		{
			if (vertices > 0 && vertices <= GRAPH_COMPLETE_MAX_VERTICES)
			{
				return true;
			}
			return false;

		}
		return false;
	}
	else if (type_.compare(GRAPH_HYPER) == 0 || type_.compare(GRAPH_CCC) == 0)
	{
		assert(inputs_map_.find("Dimension") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString d_string = inputs_map_["Dimension"];
		bool b_d;
		int dim = d_string.toInt(&b_d);
		if (b_d)
		{
			if (dim > 0 && dim <= GRAPH_HYPER_MAX_DIM)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	else if (type_.compare(GRAPH_KNODEL) == 0)
	{
		assert(inputs_map_.find("Vertices") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString v_string = inputs_map_["Vertices"];
		bool b_v;
		int vertices = v_string.toInt(&b_v);
		if (b_v)
		{
			if (vertices > 0 && vertices <= GRAPH_KNODEL_MAX_VERTICES && vertices % 2 == 0)
			{
				return true;
			}
			return false;

		}
		return false;
	}
	else if (type_.compare(GRAPH_KTREE) == 0)
	{
		if (inputs_map_.find("Height") == inputs_map_.end() || inputs_map_.find("K") == inputs_map_.end())
			return false;
		QString h_string = inputs_map_["Height"];
		QString k_string = inputs_map_["K"];
		bool b_h, b_k;
		int height = h_string.toInt(&b_h);
		int k = k_string.toInt(&b_k);
		if (b_h && b_k)
		{
			if (height > 0 && k > 0)
			{
				if (k == 1 && height < GRAPH_KTREE_MAX_VERTICES)
				{
					return true;
				}
				else if ((int(std::pow(k, height + 1)) - 1) / (k - 1) < GRAPH_KTREE_MAX_VERTICES)
				{
					return true;
				}
				return false;
			}
			return false;
		}
	}
	else if (type_.compare(GRAPH_GRID) == 0 || type_.compare(GRAPH_TORUS) == 0)
	{
		if (inputs_map_.find("N") == inputs_map_.end() || inputs_map_.find("M") == inputs_map_.end())
			return false;
		QString n_string = inputs_map_["N"];
		QString m_string = inputs_map_["M"];
		bool b_n, b_m;
		int n = n_string.toInt(&b_n);
		int m = m_string.toInt(&b_m);
		if (b_n && b_m)
		{
			if (n > 0 && m > 0)
			{
				if (n * m < GRAPH_KTREE_MAX_VERTICES)
				{

					return true;
				}
				return false;
			}
			return false;
		}
	}
	else if (type_.compare(GRAPH_RANDOM) == 0)
	{
		if (inputs_map_.find("Probability") == inputs_map_.end() || inputs_map_.find("Vertices") == inputs_map_.end())
			return false;
		QString p_string = inputs_map_["Probability"];
		QString n_string = inputs_map_["Vertices"];
		bool b_p, b_n;
		int n = n_string.toInt(&b_n);
		int p = p_string.toInt(&b_p);
		if (b_n && b_p)
		{
			if (n > 0 && p >= 0 && p <= 100)
			{
				return true;
			}
			return false;
		}
	}
	else if (type_.compare(GRAPH_BIPARTITE) == 0 || type_.compare(GRAPH_DIPPER) == 0)
	{
		if (inputs_map_.find("M") == inputs_map_.end() || inputs_map_.find("N") == inputs_map_.end())
			return false;
		QString m_string = inputs_map_["M"];
		QString n_string = inputs_map_["N"];
		bool b_m, b_n;
		int m = m_string.toInt(&b_m);
		int n = n_string.toInt(&b_n);
		if (b_n && b_n)
		{
			if (n > 0 && m > 0)
			{
				return true;
			}
			return false;
		}
	}
	else if (type_.compare(GRAPH_RAND_TREE) == 0)
	{
		if (inputs_map_.find("Children") == inputs_map_.end() || inputs_map_.find("Height") == inputs_map_.end())
			return false;
		QString c_string = inputs_map_["Children"];
		QString h_string = inputs_map_["Height"];
		bool b_c, b_h;
		int c = c_string.toInt(&b_c);
		int h = h_string.toInt(&b_h);
		if (b_c && b_h)
		{
			if (c > 0 && h > 0)
			{
				return true;
			}
			return false;
		}
	}
	else if (type_.compare(GRAPH_FIXED_RAND_TREE) == 0)
	{
		assert(inputs_map_.find("Vertices") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString v_string = inputs_map_["Vertices"];
		bool b_v;
		int vertices = v_string.toInt(&b_v);
		if (b_v)
		{
			if (vertices > 0)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

// Slots

void GraphOptionsInputDialog::okButtonClicked()
{
	options_.type_ = type_;
	if (inputs_map_.find("Height") != inputs_map_.end())
		options_.height_ = inputs_map_["Height"].toInt();
	if (inputs_map_.find("K") != inputs_map_.end())
		options_.k_ = inputs_map_["K"].toInt();
	if (inputs_map_.find("Vertices") != inputs_map_.end())
		options_.n_vertices_ = inputs_map_["Vertices"].toInt();
	if (inputs_map_.find("Dimension") != inputs_map_.end())
		options_.dim_ = inputs_map_["Dimension"].toInt();
	if (inputs_map_.find("M") != inputs_map_.end())
		options_.m_ = inputs_map_["M"].toInt();
	if (inputs_map_.find("N") != inputs_map_.end())
		options_.n_ = inputs_map_["N"].toInt();
	if (inputs_map_.find("Probability") != inputs_map_.end())
		options_.p_ = double(inputs_map_["Probability"].toInt() / 100.0);
	if (inputs_map_.find("Children") != inputs_map_.end())
		options_.children_ = inputs_map_["Children"].toInt();
	accept();
}

void GraphOptionsInputDialog::cancelButtonClicked()
{
	reject();
}

void GraphOptionsInputDialog::reject()
{
	QDialog::reject();
	Q_EMIT finishedInput(QDialog::Rejected, options_);
}


void GraphOptionsInputDialog::accept()
{
	QDialog::reject();
	Q_EMIT finishedInput(QDialog::Accepted, options_);
}




