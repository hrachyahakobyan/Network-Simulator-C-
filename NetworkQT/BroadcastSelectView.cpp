#include "stdafx.h"
#include "BroadcastSelectView.h"

BroadcastSelectView::BroadcastSelectView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.okButton->setEnabled(false);
	op_map_.insert(std::make_pair(QString("M1"), BroadcastSchemeOptions(SEND_SCHEME_M1, RECEIVE_SCHEME_M, FINISH_SCHEME_M)));
	op_map_.insert(std::make_pair(QString("M2"), BroadcastSchemeOptions(SEND_SCHEME_M2, RECEIVE_SCHEME_M, FINISH_SCHEME_M)));
	op_map_.insert(std::make_pair(QString("M3"), BroadcastSchemeOptions(SEND_SCHEME_M3, RECEIVE_SCHEME_M, FINISH_SCHEME_M)));
}

BroadcastSelectView::~BroadcastSelectView()
{

}


void BroadcastSelectView::on_broadcastTypeBox_currentIndexChanged(QString s)
{
	qDebug() << "BroadcastSelectView: changed index";
	int index = ui.broadcastTypeBox->currentIndex();
	if (index != 0)
	{
		options_ = op_map_[ui.broadcastTypeBox->currentText()];
		ui.okButton->setEnabled(true);
	}
	else
	{
		ui.okButton->setEnabled(false);
	}
}

void BroadcastSelectView::on_okButton_clicked()
{
	accept();
}


void BroadcastSelectView::accept()
{
	QDialog::accept();
	ui.okButton->setEnabled(false);
	ui.broadcastTypeBox->setCurrentIndex(0);
	Q_EMIT broadcastDialogFinishedSelect(QDialog::Accepted, options_);
}


void BroadcastSelectView::reject()
{
	QDialog::reject();
	ui.okButton->setEnabled(false);
	ui.broadcastTypeBox->setCurrentIndex(0);
	Q_EMIT broadcastDialogFinishedSelect(QDialog::Rejected, options_);
}