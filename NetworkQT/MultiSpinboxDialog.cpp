#include "stdafx.h"
#include "MultiSpinboxDialog.h"

MultiSpinboxDialog::MultiSpinboxDialog(QWidget *parent)
	: QDialog(parent)
{

}

MultiSpinboxDialog::MultiSpinboxDialog(QWidget *parent, QList<QPair<QString, QPair<int, int>>> spinBoxes, QString title)
	: QDialog(parent)
{
	form_ = new QFormLayout(this);
	form_->addRow(new QLabel(title));

	for (int i = 0; i < spinBoxes.size(); i++)
	{
		QSpinBox *box = new QSpinBox(this);
		box->setRange(spinBoxes.at(i).second.first, spinBoxes.at(i).second.second);
		form_->addRow(spinBoxes.at(i).first, box);
		spinBoxes_ << qMakePair(spinBoxes.at(i).first, box);
		connect(box, SIGNAL(valueChanged(const QString&)), this, SLOT(spinBoxChanged(const QString&)));
	}

	ok_button_ = new QPushButton("Ok");
	cancel_button_ = new QPushButton("Cancel");
	buttons_ = new QDialogButtonBox(Qt::Horizontal, this);
	buttons_->addButton(ok_button_, QDialogButtonBox::ButtonRole::AcceptRole);
	buttons_->addButton(cancel_button_, QDialogButtonBox::ButtonRole::RejectRole);
	form_->addRow(buttons_);
	connect(buttons_, SIGNAL(accepted()), this, SLOT(okButtonClicked()));
	connect(buttons_, SIGNAL(rejected()), this, SLOT(cancelButtonClicked()));
	updateValues();
}


MultiSpinboxDialog::~MultiSpinboxDialog()
{
	delete form_;
	delete buttons_;
	spinBoxes_.clear();
}

void MultiSpinboxDialog::spinBoxChanged(const QString& text)
{
	updateValues();
}

void MultiSpinboxDialog::updateValues()
{
	QList<QPair<QString, QSpinBox*>>::iterator it;
	for (it = spinBoxes_.begin(); it != spinBoxes_.end(); ++it)
	{
		inputs_map_[(*it).first] = (*it).second->value();
	}
}

void MultiSpinboxDialog::cancelButtonClicked()
{
	qDebug() << "Cancel button clicked \n";
	reject();
}

void MultiSpinboxDialog::okButtonClicked()
{
	qDebug() << "Ok button clicked \n";
	accept();
}

void MultiSpinboxDialog::accept()
{
	QDialog::accept();
	Q_EMIT multiSpinboxDialogDidFinish(QDialog::Accepted, inputs_map_);
}


void MultiSpinboxDialog::reject()
{
	QDialog::reject();
	Q_EMIT multiSpinboxDialogDidFinish(QDialog::Rejected, inputs_map_);
}

bool MultiSpinboxDialog::validate()
{
	return true;
	bool valid = true;
	QList<QPair<QString, QSpinBox*>>::iterator it;
	for (it = spinBoxes_.begin(); it != spinBoxes_.end(); ++it)
	{
		int val = (*it).second->value();
		valid &= (val >= (*it).second->minimum() && val <= (*it).second->maximum());
	}
	return valid;
}

