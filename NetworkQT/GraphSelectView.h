#ifndef GRAPHSELECTVIEW_H
#define GRAPHSELECTVIEW_H

#include "ui_GraphSelectView.h"

struct GraphOptions
{
	std::string type_;
};

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
private:
	Ui::GraphSelectView ui;
public Q_SLOTS:
	void on_graphTypeBox_currentIndexChanged(QString s);
	void on_okButton_clicked();

};

#endif // GRAPHSELECTVIEW_H
