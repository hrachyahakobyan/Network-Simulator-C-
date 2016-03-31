#include "stdafx.h"
#include "BroadcastSessionView.h"

BroadcastSessionView::BroadcastSessionView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
}

BroadcastSessionView::BroadcastSessionView(QWidget* parent, std::unique_ptr<HNABroadcastSession> session)
	: QDialog(parent), session_(std::move(session))
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
	draw((*session_).last());
}

BroadcastSessionView::~BroadcastSessionView()
{
	session_.reset();
	imageScene_->clear();
	delete imageScene_;
}

void BroadcastSessionView::on_saveButton_clicked()
{
	qDebug() << "BroadcastView save button clicked \n";
	QString dir = QFileDialog::getExistingDirectory(this, tr("Choose folder"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	boost::filesystem::path dest_path(dir.toLocal8Bit().constData());
	if (dir.size() > 0)
	{
		(*session_).save(dest_path);
	}
}

void BroadcastSessionView::on_tickButton_clicked()
{
	qDebug() << "BroadcastView tick button clicked \n";
	(*session_).tick(ui.tickSpinBox->value());
	draw((*session_).last());
}

void BroadcastSessionView::on_finishButton_clicked()
{
	qDebug() << "BroadcastView finish button clicked \n";
}

void BroadcastSessionView::on_nextButton_clicked()
{
	qDebug() << "BroadcastView next button clicked \n";
	draw((*session_).next());
}

void BroadcastSessionView::on_previousButton_clicked()
{
	qDebug() << "BroadcastView prev button clicked \n";
	draw((*session_).previous());
}


void BroadcastSessionView::on_tickSpinBox_valueChanged(int v)
{
	if (v < 1)
	{
		ui.tickSpinBox->setValue(1);
	}
}

void BroadcastSessionView::accept()
{
	QDialog::accept();
	Q_EMIT sessionViewDidFinish(QDialog::Accepted);
}

void BroadcastSessionView::reject()
{
	QDialog::reject();
	Q_EMIT sessionViewDidFinish(QDialog::Rejected);
}

void BroadcastSessionView::draw(const boost::filesystem::path& img)
{
	image_.load(img.string().c_str());
	imageScene_->clear();
	imageScene_->addPixmap(image_);
	imageScene_->setSceneRect(image_.rect());
	ui.graphicsView->setScene(imageScene_);
}

void BroadcastSessionView::buildEditInputDialog()
{

}