#ifndef BROADCASTTESTVIEW_H
#define BROADCASTTESTVIEW_H

#include <QDialog>
#include "ui_BroadcastTestView.h"
#include "GraphSelectView.h"
#include "BroadcastSelectView.h"
#include "BroadcastTest.h"

class BroadcastTestThread : public QThread, SimTestCallBack
{	

	Q_OBJECT

public:
	BroadcastTestThread() {
		sOp_ = BroadcastSchemeOptions(SEND_SCHEME_M1, RECEIVE_SCHEME_M, FINISH_SCHEME_M);
		gOp_ = GraphBuilder::GraphOptions();
		gOp_.type_ = GraphBuilder::GraphOptions::GraphType::Graph_Complete;
		gOp_.n_vertices_ = 10;
		tOp_ = TestOptions();
		tOp_.iterCount_ = 1;
	}
	~BroadcastTestThread() {}
	void setSchemeOptions(const BroadcastSchemeOptions& sOp){
		sOp_ = sOp;
	}
	void setGraphOptions(const GraphBuilder::GraphOptions& gOp)
	{
		gOp_ = gOp;
	}
	void setTestOptions(const TestOptions& tOp){
		tOp_ = tOp;
	}
	bool isRunning(){
		return bTest_.isRunning_;
	}
	void cancel(){
		bTest_.cancel();
	}
	void testCallback(int it, double t, bool f, std::string filename = "") {
		Q_EMIT broadcastThreadDidUpdate(it, t, f, QString(filename.c_str()));
	}
private:
	BroadcastSchemeOptions sOp_;
	GraphBuilder::GraphOptions gOp_;
	TestOptions tOp_;
	BroadcastTest bTest_;
	void run(){
		bTest_.test(gOp_, sOp_, tOp_, this);
	}
Q_SIGNALS:
	void broadcastThreadDidUpdate(int it, double t, bool f, QString filename = "");
};

class BroadcastTestView : public QDialog
{
	Q_OBJECT

public:
	BroadcastTestView(QWidget *parent = 0);
	~BroadcastTestView();
	void reject();

public Q_SLOTS:
	void on_startButton_clicked();
	void on_cancelButton_clicked();
	void on_saveButton_clicked();
	void on_broadcastButton_clicked();
	void on_graphButton_clicked();
	void onIterationCountSpinBoxValueChanged(const QString& text);
	void on_graphSelectViewFinished(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& path);
	void on_broadcastSelectViewFinished(int state, const BroadcastSchemeOptions& options);
	void on_broadcastTestDidUpdate(int it, double t, bool f, QString);
	void on_broadcastTestDidFinish();
private:
	Ui::BroadcastTestView ui;
	std::map<QString, BroadcastSchemeOptions> op_map_;
	BroadcastSelectView* broadcastView_;
	GraphSelectView* graphView_;
	BroadcastTestThread* testThread_;
	boost::filesystem::path statPath_;
};

#endif // BROADCASTTESTVIEW_H
