#ifndef GRAPHSELECTVIEW_H
#define GRAPHSELECTVIEW_H

#include "ui_GraphSelectView.h"
#include "GraphManager.h"

class GraphSelectViewDelegate
{
public:

};

class GraphSelectView : public QDialog
{
	Q_OBJECT

public:
	GraphSelectView(QWidget *parent = 0);
	~GraphSelectView();
	void reject();
	bool shouldSave_;
public Q_SLOTS:
	void on_graphTypeBox_currentIndexChanged(QString s);
	void on_okButton_clicked();
private:
	Ui::GraphSelectView ui;
	boost::filesystem::path graph_path_;
	GraphOptions options_;
	std::map<int, std::string> type_mapper_;
	QGraphicsScene* imageScene_;
	QPixMap image_;
};

#endif // GRAPHSELECTVIEW_H
