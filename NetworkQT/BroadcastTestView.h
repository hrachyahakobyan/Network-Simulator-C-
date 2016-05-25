#ifndef BROADCASTTESTVIEW_H
#define BROADCASTTESTVIEW_H

#include <QDialog>
#include "ui_BroadcastTestView.h"
#include "GraphSelectView.h"
#include "BroadcastSelectView.h"
#include "BroadcastTest.h"

class BroadcastTestView : public QDialog
{
	Q_OBJECT

public:
	BroadcastTestView(QWidget *parent = 0);
	~BroadcastTestView();

public Q_SLOTS:
	void on_startButton_clicked();
	void on_cancelButton_clicked();
	void on_saveButton_clicked();
	void on_broadcastButton_clicked();
	void on_graphButton_clicked();

	void onIterationCountSpinBoxValueChanged(const QString& text);

	void on_graphSelectViewFinished(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& path);
	void on_broadcastSelectViewFinished(int state, const BroadcastSchemeOptions& options);

private:
	Ui::BroadcastTestView ui;
	std::map<QString, BroadcastSchemeOptions> op_map_;
	BroadcastSelectView* broadcastView_;
	GraphSelectView* graphView_;
	BroadcastSchemeOptions schemeOp_;
	GraphBuilder::GraphOptions graphOp_;
	TestOptions testOp_;
	BroadcastTest broadTest_;
};

#endif // BROADCASTTESTVIEW_H
