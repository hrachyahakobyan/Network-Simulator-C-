#include "stdafx.h"
#include "CompleteGraphInputDialog.h"

CompleteGraphInputDialog::CompleteGraphInputDialog(QWidget *parent)
	: MultiInputDialog(parent, QList<QString>({ "Vertices" }), "Complete Graph Options")
{
	for each (QLineEdit* lineEdit in lines_)
	{
		lineEdit->setValidator(new QIntValidator(1, 30, this));
	}
}

CompleteGraphInputDialog::~CompleteGraphInputDialog()
{

}

bool CompleteGraphInputDialog::validate()
{
	return true;
}