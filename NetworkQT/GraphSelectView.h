#ifndef GRAPHSELECTVIEW_H
#define GRAPHSELECTVIEW_H

#include "ui_GraphSelectView.h"
#include "GraphManager.h"
#include "CompleteGraphInputDialog.h"

class GraphSelectView;

class GraphSelectViewDelegate
{
public:
	virtual void graphSelectViewDidSaveGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path) = 0;
	virtual void graphSelectViewDidSelectGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path) = 0;
};

class GraphSelectView : public QDialog
{
	Q_OBJECT

public:
	GraphSelectView(QWidget *parent = 0);
	~GraphSelectView();
	void reject();
	bool shouldSave_;
	GraphSelectViewDelegate* delegate_;
public Q_SLOTS:
	void on_graphTypeBox_currentIndexChanged(QString s);
	void on_okButton_clicked();
private:
	Ui::GraphSelectView ui;
	boost::filesystem::path graph_path_;
	boost::filesystem::path folder_path_;
	GraphOptions options_;
	std::map<int, std::string> type_mapper_;
	QGraphicsScene* imageScene_;
	QPixmap image_;
	MultiInputDialog* dialog_;

	void disappear();
};

#endif // GRAPHSELECTVIEW_H
