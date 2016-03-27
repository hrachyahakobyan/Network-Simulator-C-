#ifndef COMPLETEGRAPHINPUTDIALOG_H
#define COMPLETEGRAPHINPUTDIALOG_H

#include "MultiInputDialog.h"

class CompleteGraphInputDialog : public MultiInputDialog
{
	Q_OBJECT

public:
	CompleteGraphInputDialog(QWidget *parent);
	~CompleteGraphInputDialog();

private:

protected:
	bool validate();
	
};

#endif // COMPLETEGRAPHINPUTDIALOG_H
