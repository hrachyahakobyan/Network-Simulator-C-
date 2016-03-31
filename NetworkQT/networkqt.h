#ifndef NETWORKQT_H
#define NETWORKQT_H

#include "ui_networkqt.h"
#include "GraphSelectView.h"
#include "BroadcastSelectView.h"
#include "HNABroadcastSession.h"
#include "BroadcastSessionView.h"

class NetworkQT : public QMainWindow
{
	Q_OBJECT

public:
	NetworkQT(QWidget *parent = 0);
	~NetworkQT();

private:
	Ui::NetworkQTClass ui;
	GraphSelectView* graphSelectView_;
	BroadcastSelectView* broadcastSelectView_;
	BroadcastSessionView* broadcastSessionView_;
	GraphOptions g_op_;
	BroadcastSchemeOptions s_op_;
public Q_SLOTS:
	void on_actionSimulation_triggered();
	void on_actionExit_triggered();
	void on_actionGraph_triggered();
	void graphSelectViewFinished(int state, const GraphOptions& options, const boost::filesystem::path& image_path);
	void broadcastSchemeSelectViewFinished(int state, const BroadcastSchemeOptions& options);
	void broadcastSessionViewDidFinish(int state);
};

#endif // NETWORKQT_H
