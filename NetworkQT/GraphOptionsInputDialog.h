#ifndef GRAPHOPTIONSINPUTDIALOG_H
#define GRAPHOPTIONSINPUTDIALOG_H
#include "MultiInputDialog.h"
#include "GraphBuilder.h"

class GraphOptionsInputDialog : public MultiInputDialog
{
	Q_OBJECT

public:
	GraphOptionsInputDialog(QWidget *parent, QList<QString> labels, GraphBuilder::GraphOptions::GraphType type);
	~GraphOptionsInputDialog();
	void reject();
	void accept();
private:
	GraphBuilder::GraphOptions::GraphType type_;
	GraphBuilder::GraphOptions options_;
protected:
	bool validate();
public Q_SLOTS:
	void okButtonClicked();
	void cancelButtonClicked();
Q_SIGNALS:
	void finishedInput(int status, const GraphBuilder::GraphOptions& options);
};

#endif // GRAPHOPTIONSINPUTDIALOG_H
