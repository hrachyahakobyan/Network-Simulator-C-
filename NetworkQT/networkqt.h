#ifndef NETWORKQT_H
#define NETWORKQT_H

#include "ui_networkqt.h"
#include "GraphSelectView.h"
#include "BroadcastSelectView.h"
#include "DiseaseSelectView.h"
#include "SessionView.h"
#include "BroadcastTestView.h"

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
	SessionView* sessionView_;
	DiseaseSelectView* diseaseSelectView_;
	BroadcastTestView* testView_;
	GraphBuilder::GraphOptions g_op_;
	DiseaseSimulation::DiseaseOptions d_op_;
	BroadcastSchemeOptions s_op_;
	enum Simulation{Broadcast, Disease};
	Simulation sim_;
public Q_SLOTS:
	void on_actionBroadcasting_triggered();
	void on_actionDiseaseModel_triggered();
	void on_actionExit_triggered();
	void on_actionGraph_triggered();
	void on_actionTest_triggered();
	void graphSelectViewFinished(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& image_path);
	void broadcastSchemeSelectViewFinished(int state, const BroadcastSchemeOptions& options);
	void sessionViewDidFinish(int state);
	void diseaseSelectViewDidFinish(int state, const DiseaseSimulation::DiseaseOptions& options);
};

#endif // NETWORKQT_H
