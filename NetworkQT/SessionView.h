#ifndef SESSIONVIEW_H
#define SESSIONVIEW_H

#include "ui_SessionView.h"
#include "Session.h"
#include "BroadcastSessionEditInputDialog.h"

class SessionView : public QDialog
{
	Q_OBJECT
		typedef std::unique_ptr<Session> Session_Ptr;
public:
	SessionView(QWidget *parent = 0);
	SessionView(QWidget* parent, std::unique_ptr<Session> session);
	~SessionView();
	void accept();
	void reject();
private:
	Session_Ptr session_;
	QPixmap image_;
	QGraphicsScene* imageScene_;
	BroadcastSessionEditInputDialog* editDialog_;
	public Q_SLOTS:
	void on_saveButton_clicked();
	void on_tickButton_clicked();
	void on_finishButton_clicked();
	void on_nextButton_clicked();
	void on_previousButton_clicked();
	void on_redrawButton_clicked();
	void on_resetButton_clicked();
	void on_tickSpinBox_valueChanged(int v);
	void on_editTypeBox_currentIndexChanged(QString s);
	void editDialogDidFinish(int state, const GraphEditAction& action);
Q_SIGNALS:
	void sessionViewDidFinish(int status);
private:
	Ui::SessionView ui;
	std::map<std::string, int> plotIndexMap_;
	void draw(const boost::filesystem::path& img);
	void buildEditInputDialog();
	void initializeGraphView();
	void updatePlot();
	Qt::GlobalColor convert(Color color);
};

#endif // SESSIONVIEW_H
