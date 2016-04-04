#ifndef GRAPHSELECTVIEW_H
#define GRAPHSELECTVIEW_H

#include "ui_GraphSelectView.h"
#include "GraphManager.h"
#include "GraphOptionsInputDialog.h"

class GraphSelectView : public QDialog
{
	Q_OBJECT

public:
	GraphSelectView(QWidget *parent = 0);
	~GraphSelectView();
	void reject();
	void accept();
	bool shouldSave_;
public Q_SLOTS:
	void on_graphTypeBox_currentIndexChanged(QString s);
	void on_okButton_clicked();
	void inputDialogFinished(int status, const GraphBuilder::GraphOptions& options);
Q_SIGNALS:
	void finishedSelect(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& image_path);
private:
	Ui::GraphSelectView ui;

	boost::filesystem::path graph_path_;
	boost::filesystem::path folder_path_;
	std::map<int, GraphBuilder::GraphOptions::GraphType> type_mapper_;
	GraphBuilder::GraphOptions options_;

	QGraphicsScene* imageScene_;
	QPixmap image_;
	GraphOptionsInputDialog* dialog_;

	void buildInputDialog(GraphBuilder::GraphOptions::GraphType type);
};

#endif // GRAPHSELECTVIEW_H
