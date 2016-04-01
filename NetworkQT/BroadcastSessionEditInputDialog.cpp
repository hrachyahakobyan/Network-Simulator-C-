#include "stdafx.h"
#include "BroadcastSessionEditInputDialog.h"

BroadcastSessionEditInputDialog::BroadcastSessionEditInputDialog(QWidget *parent, QList<QString> labels, GraphEditAction::EditType editType)
	: MultiInputDialog(parent, labels)
{
	for each (QLineEdit* line in lines_)
	{
		line->setValidator(new QIntValidator(0, 1000, this));
	}
	action_.type_ = editType;
}

BroadcastSessionEditInputDialog::~BroadcastSessionEditInputDialog()
{

}


bool BroadcastSessionEditInputDialog::validate()
{
	if (action_.type_ == GraphEditAction::EditType::AddEdge || action_.type_ == GraphEditAction::EditType::DeleteEdge)
	{
		if (inputs_map_.find("Source") != inputs_map_.end() && inputs_map_.find("Target") != inputs_map_.end())
		{
			if (inputs_map_["Source"].toInt() < 0 || inputs_map_["Target"].toInt() < 0 ||
				inputs_map_["Source"].toInt() == inputs_map_["Target"].toInt())
				return false;
			else
			{
				action_.src_ = inputs_map_["Source"].toInt();
				action_.targ_ = inputs_map_["Target"].toInt();
				return true;
			}
		}
		return false;
	}
	else if (action_.type_ == GraphEditAction::EditType::SetState) 
	{
		if (inputs_map_.find("Vertex") != inputs_map_.end() && inputs_map_.find("State") != inputs_map_.end())
		{
			if (inputs_map_["Vertex"].toInt() < 0 || inputs_map_["State"].toInt() < 0)
				return false;
			else
			{
				action_.v_ = inputs_map_["Vertex"].toInt();
				action_.state_ = inputs_map_["State"].toInt();
				return true;
			}
		}
		return false;
	}
	else if (action_.type_ == GraphEditAction::EditType::AddVertex)
	{
		if (inputs_map_.find("State") != inputs_map_.end())
		{
			if (inputs_map_["State"].toInt() < 0)
				return false;
			else
			{
				action_.state_ = inputs_map_["State"].toInt();
				return true;
			}
		}
		return false;
	}
	else
	{
		if (inputs_map_.find("Vertex") != inputs_map_.end())
		{
			if (inputs_map_["Vertex"].toInt() < 0)
				return false;
			else
			{
				action_.v_ = inputs_map_["Vertex"].toInt();
				return true;
			}
		}
		return false;
	}
	return true;
}


void BroadcastSessionEditInputDialog::okButtonClicked()
{
	accept();
}


void BroadcastSessionEditInputDialog::cancelButtonClicked()
{
	reject();
}


void BroadcastSessionEditInputDialog::accept()
{
	QDialog::accept();
	Q_EMIT editDialogDidFinish(QDialog::Accepted, action_);
}

void BroadcastSessionEditInputDialog::reject()
{
	QDialog::reject();
	Q_EMIT editDialogDidFinish(QDialog::Rejected, action_);
}