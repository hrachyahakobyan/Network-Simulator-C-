#include "stdafx.h"
#include "MultiInputDialog.h"

MultiInputDialog::MultiInputDialog(QWidget *parent)
	: QDialog(parent)
{

}
MultiInputDialog::MultiInputDialog(QWidget* parent, QList<QString> labels, QString title)
	: QDialog(parent)
{
	form_ = new QFormLayout(this);
	form_->addRow(new QLabel(title));

	for (int i = 0; i < labels.size(); i++)
	{
		QLineEdit *lineEdit = new QLineEdit(this);
		form_->addRow(labels.at(i), lineEdit);
		lines_ << lineEdit;
		lines_map_[i] = labels.at(i);
		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineTextChanged(const QString&)));
	}

	ok_button_ = new QPushButton("Ok");
	cancel_button_ = new QPushButton("Cancel");
	buttons_ = new QDialogButtonBox(Qt::Horizontal, this);
	buttons_->addButton(ok_button_, QDialogButtonBox::ButtonRole::AcceptRole);
	buttons_->addButton(cancel_button_, QDialogButtonBox::ButtonRole::RejectRole);
	form_->addRow(buttons_);
	connect(buttons_, SIGNAL(accepted()), this, SLOT(okButtonClicked()));
	connect(buttons_, SIGNAL(rejected()), this, SLOT(cancelButtonClicked()));
	ok_button_->setEnabled(false);

}

MultiInputDialog::~MultiInputDialog()
{
	delete form_;
	delete buttons_;
	lines_.clear();
}


void MultiInputDialog::cancelButtonClicked()
{
	qDebug() << "Cancel button clicked \n";
	done(QDialog::Rejected);
}

void MultiInputDialog::okButtonClicked()
{
	qDebug() << "Ok button clicked \n";
	done(QDialog::Accepted);
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