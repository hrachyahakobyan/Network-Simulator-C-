#ifndef BROADCASTSESSIONVIEW_H
#define BROADCASTSESSIONVIEW_H

#include <QDialog>
#include "ui_BroadcastSessionView.h"
#include "HNABroadcastSession.h"
#include "BroadcastSessionEditInputDialog.h"

class BroadcastSessionView : public QDialog
{
	Q_OBJECT
		typedef std::unique_ptr<HNABroadcastSession> Session;
public:
	BroadcastSessionView(QWidget *parent = 0);
	BroadcastSessionView(QWidget* parent, std::unique_ptr<HNABroadcastSession> session);
	~BroadcastSessionView();
	void accept();
	void reject();
private:
	Session session_;
	QPixmap image_;
	QGraphicsScene* imageScene_;
	BroadcastSessionEditInputDialog* editDialog_;
public Q_SLOTS:
	void on_saveButton_clicked();
	void on_tickButton_clicked();
	void on_finishButton_clicked();
	void on_nextButton_clicked();
	void on_previousButton_clicked();
	void on_tickSpinBox_valueChanged(int v);
	void editDialogDidFinish(int state, const GraphEditAction& action);
Q_SIGNALS:
	void sessionViewDidFinish(int status);
private:
	Ui::BroadcastSessionView ui;
	void draw(const boost::filesystem::path& img);
	void buildEditInputDialog();
};

#endif // BROADCASTSESSIONVIEW_H
