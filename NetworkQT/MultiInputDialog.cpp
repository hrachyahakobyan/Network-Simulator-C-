#include "stdafx.h"
#include "MultiInputDialog.h"

MultiInputDialog::MultiInputDialog(QWidget *parent)
	: QDialog(parent)
{

}
MultiInputDialog::MultiInputDialog(QWidget* parent, QList<QString> labels, QString title)
	: QDialog(parent), labels_(labels), delegate_(NULL)
{
	form_ = new QFormLayout(this);
	form_->addRow(new QLabel(title));

	for (int i = 0; i < labels.size(); i++)
	{
		QLineEdit *lineEdit = new QLineEdit(this);
		form_->addRow(labels_.at(i), lineEdit);
		lines_ << lineEdit;
		lines_map_[i] = labels_.at(i);
		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineTextChanged(const QString&)));
	}

	ok_button_ = new QPushButton("My Ok Button");
	cancel_button_ = new QPushButton("My Cancel Button");
	buttons_ = new QDialogButtonBox(Qt::Horizontal, this);
	buttons_->addButton(ok_button_, QDialogButtonBox::ButtonRole::AcceptRole);
	buttons_->addButton(cancel_button_, QDialogButtonBox::ButtonRole::RejectRole);
	form_->addRow(buttons_);
	connect(buttons_, SIGNAL(accepted()), this, SLOT(okButtonClicked()));
	connect(buttons_, SIGNAL(rejected()), this, SLOT(cancelButtonClicked()));

}

MultiInputDialog::~MultiInputDialog()
{
	lines_.clear();
	delete form_;
	delete buttons_;
}


void MultiInputDialog::cancelButtonClicked()
{
	qDebug() << "Cancel button clicked \n";
}

void MultiInputDialog::okButtonClicked()
{
	qDebug() << "Ok button clicked \n";
	if (delegate_ != NULL)
	{
		delegate_->multiInputDialogDidDismissWithInputs(this, inputs_map_);
		close();
	}
}

void MultiInputDialog::lineTextChanged(const QString& string)
{
	QObject* send = sender();
	int index = lines_.indexOf(qobject_cast<QLineEdit*>(sender()));
	qDebug() << "Line at index " << index << "Did change text \n " << string << "\n";
	inputs_map_[lines_map_[index]] = string;
	if (validate() == true)
	{
		qDebug() << "Validation successful\n";
		ok_button_->setEnabled(true);
	}
	else
	{
		qDebug() << "Validation failed\n";
		ok_button_->setEnabled(false);
	}
}

bool MultiInputDialog::validate()
{
	return true;
}