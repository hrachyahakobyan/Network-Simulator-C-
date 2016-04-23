#ifndef BROADCASTSELECTVIEW_H
#define BROADCASTSELECTVIEW_H

#include "ui_BroadcastSelectView.h"
#include "BroadcastScheme.h"

class BroadcastSelectView : public QDialog
{
	Q_OBJECT

public:
	BroadcastSelectView(QWidget *parent = 0);
	~BroadcastSelectView();
	void accept();
	void reject();
private:
	Ui::BroadcastSelectView ui;
	BroadcastSchemeOptions options_;
	std::map<QString, BroadcastSchemeOptions> op_map_;

public Q_SLOTS:
	void on_broadcastTypeBox_currentIndexChanged(QString s);
	void on_okButton_clicked();
Q_SIGNALS:
	void broadcastDialogFinishedSelect(int state, const BroadcastSchemeOptions& options);
};

#endif // BROADCASTSELECTVIEW_H
