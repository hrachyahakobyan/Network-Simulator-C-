#ifndef GRAPHSELECTVIEW_H
#define GRAPHSELECTVIEW_H

#include "ui_GraphSelectView.h"
#include "GraphManager.h"
#include "GraphOptionsInputDialog.h"
#include "MultiSpinboxDialog.h"

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
	void spinDialogDidFinish(int status, const QMap<QString, int>& input);
Q_SIGNALS:
	void finishedSelect(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& image_path);
private:
	Ui::GraphSelectView ui;

	boost::filesystem::path graph_path_;
	boost::filesystem::path folder_path_;
	GraphBuilder::GraphOptions options_;

	QGraphicsScene* imageScene_;
	QPixmap image_;
	GraphOptionsInputDialog* dialog_;
	MultiSpinboxDialog* spinDialog_;
	QMap<int, QPair<GraphBuilder::GraphOptions::GraphType, QList<QString>>> inputMap_;
	QMap<GraphBuilder::GraphOptions::GraphType, QList<QPair<QString, QPair<int, int>>>> spinBoxMap_;

	void buildSpinDialog(GraphBuilder::GraphOptions::GraphType type);
	void parseInput(const QMap<QString, int>& input, GraphBuilder::GraphOptions& options);
};

#endif // GRAPHSELECTVIEW_H
