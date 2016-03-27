#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false)
{
	ui.setupUi(this);
	ui.okButton->setDisabled(true);
	imageScene_ = new QGraphicsScene(this);
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
	type_mapper_.insert(std::make_pair(2, GRAPH_HYPER));
	type_mapper_.insert(std::make_pair(3, GRAPH_KNODEL));
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
}

GraphSelectView::~GraphSelectView()
{
	delete imageScene_;
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
		
		options_.type_ = type_mapper_.at(index);


		//get other options

		//show image
		graph_path_ = GraphManager::sharedManager()->graphImageWithOptions(options_);
		image_.load(graph_path_.string());
		imageScene_->clear();
		imageScene_->addPixmap(image_);
		ui.graphicsView->setScene(imageScene_);
		ui.okButton->setEnabled(true);
	}
}


void GraphSelectView::on_okButton_clicked()
{
	qDebug() << "GraphSelectView: ok button click \n";
	if (shouldSave_ == true)
	{
		qDebug() << "GraphSelectView: saving graph \n";
		QString dir = QFileDialog::getExistingDirectory(this, tr("Choose folder"),
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
		resBtn = QMessageBox::question(this, "Close Graph",
			tr("Are you sure?\n"),
			QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	}
	if (resBtn == QMessageBox::Yes) {
		QDialog::reject();
	}
}