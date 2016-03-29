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
	void inputDialogFinished(int status, const GraphOptions& options);
Q_SIGNALS:
	void finishedSelect(int state, const GraphOptions& options, const boost::filesystem::path& image_path);
private:
	Ui::GraphSelectView ui;
	boost::filesystem::path graph_path_;
	boost::filesystem::path folder_path_;
	GraphOptions options_;
	std::map<int, std::string> type_mapper_;
	QGraphicsScene* imageScene_;
	QPixmap image_;
	GraphOptionsInputDialog* dialog_;
};

#endif // GRAPHSELECTVIEW_H
