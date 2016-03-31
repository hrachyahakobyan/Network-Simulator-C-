#ifndef BROADCASTSESSIONEDITINPUTDIALOG_H
#define BROADCASTSESSIONEDITINPUTDIALOG_H

#include "MultiInputDialog.h"
#include "BroadcastSimulation.h"

class BroadcastSessionEditInputDialog : public MultiInputDialog
{
	Q_OBJECT

public:
	BroadcastSessionEditInputDialog(QWidget *parent, QList<QString> labels, GraphEditAction::EditType editType);
	~BroadcastSessionEditInputDialog();
	void reject();
	void accept();
protected:
	bool validate();
public Q_SLOTS:
	void okButtonClicked();
	void cancelButtonClicked();
Q_SIGNALS :
	void editDialogDidFinish(int state, const GraphEditAction& edit);
private:
	GraphEditAction action_;
};

#endif // BROADCASTSESSIONEDITINPUTDIALOG_H
