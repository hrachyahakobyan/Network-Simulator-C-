#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false)
{
	ui.setupUi(this);
	ui.okButton->setDisabled(true);
}

GraphSelectView::~GraphSelectView()
{

}

void GraphSelectView::on_graphTypeBox_currentIndexChanged(QString s)
{
	qDebug() << "GraphSelectView: graphTypeBox index changed";
	qDebug() << s;
	qDebug() << "\n";
	int index = ui.graphTypeBox->currentIndex();
	if (index == 0)
	{
		ui.okButton->setDisabled(true);
	}
	else
	{
		ui.okButton->setEnabled(true);
	}
}


void GraphSelectView::on_okButton_clicked()
{
	qDebug() << "GraphSelectView: ok button click \n";
	if (shouldSave_ == true)
	{
		qDebug() << "GraphSelectView: saving graph \n";
		QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
			"/home",
			QFileDialog::ShowDirsOnly
			| QFileDialog::DontResolveSymlinks);
		std::string current_locale_text = dir.toLocal8Bit().constData();
	}
	else
	{

	}
}

void GraphSelectView::reject()
{
	// handle close action
	QMessageBox::StandardButton resBtn = QMessageBox::Yes;
	if (0) {
		resBtn = QMessageBox::question(this, "Fuck",
			tr("Are you sure?\n"),
			QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	}
	if (resBtn == QMessageBox::Yes) {
		QDialog::reject();
	}
}