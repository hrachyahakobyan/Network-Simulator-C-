#ifndef GRAPHOPTIONSINPUTDIALOG_H
#define GRAPHOPTIONSINPUTDIALOG_H

#include "MultiInputDialog.h"
#include "HNAGraphFactory.h"
class GraphOptionsInputDialog : public MultiInputDialog
{
	Q_OBJECT

public:
	GraphOptionsInputDialog(QWidget *parent, const std::string& type);
	~GraphOptionsInputDialog();
	void reject();
	void accept();
private:
	std::string type_;
	GraphOptions options_;
protected:
	bool validate();
public Q_SLOTS:
	void okButtonClicked();
	void cancelButtonClicked();
Q_SIGNALS:
	void finishedInput(int status, const GraphOptions& options);
};

#endif // GRAPHOPTIONSINPUTDIALOG_H
