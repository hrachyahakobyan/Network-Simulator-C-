#ifndef NETWORKQT_H
#define NETWORKQT_H

#include "ui_networkqt.h"
#include "GraphSelectView.h"

class NetworkQT : public QMainWindow, public GraphSelectViewDelegate
{
	Q_OBJECT

public:
	NetworkQT(QWidget *parent = 0);
	~NetworkQT();

private:
	Ui::NetworkQTClass ui;
	GraphSelectView* graphSelectView_;
public Q_SLOTS:
	void on_actionSimulation_triggered();
	void on_actionExit_triggered();
	void on_actionGraph_triggered();
	void on_pushButton_clicked();

// GraphSelectViewDelegate
public:
	void graphSelectViewDidSaveGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path);
	void graphSelectViewDidSelectGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path);
};

#endif // NETWORKQT_H
