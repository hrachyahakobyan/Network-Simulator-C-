#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false), delegate_(NULL)
{
	ui.setupUi(this);
	ui.okButton->setDisabled(true);
	imageScene_ = new QGraphicsScene(this);
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
	type_mapper_.insert(std::make_pair(2, GRAPH_HYPER));
	type_mapper_.insert(std::make_pair(3, GRAPH_KNODEL));
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
	type_mapper_.insert(std::make_pair(1, GRAPH_COMPLETE));
	shouldSave_ = true;

	int inputs = 3;
	QList<QString> labels({ "1", "2", "3" });
	dialog_ = new CompleteGraphInputDialog(this);
	dialog_->hide();
}

GraphSelectView::~GraphSelectView()
{
	delete imageScene_;
	delete dialog_;
}

void GraphSelectView::on_graphTypeBox_currentIndexChanged(QString s)
{
	qDebug() << "GraphSelectView: graphTypeBox index changed";
	qDebug() << s;
	qDebug() << "\n";
	int index = ui.graphTypeBox->currentIndex();
	if (index == 0 && ui.okButton->isEnabled() == false)
	{
		ui.okButton->setDisabled(true);
	}
	else if (index != 0)
	{	
		options_.type_ = type_mapper_.at(index);
		options_.dim_ = 3;
		options_.n_vertices_ = 21;
		//get other options
		dialog_->show();
		//show image
		GraphManager::sharedManager()->graphImageWithOptions(options_, graph_path_, folder_path_);
		image_.load(graph_path_.string().c_str());
		imageScene_->clear();
		imageScene_->addPixmap(image_);
		imageScene_->setSceneRect(image_.rect());
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
		boost::filesystem::path dest_path(dir.toLocal8Bit().constData());
		GraphManager::sharedManager()->saveGraphImage(folder_path_, dest_path);
		if (delegate_ != NULL)
		{
			delegate_->graphSelectViewDidSaveGraph(this, options_, graph_path_);
		}
		disappear();
	}
	else
	{
		qDebug() << "GraphSelectView: selecting graph \n";
		if (delegate_ != NULL)
		{
			delegate_->graphSelectViewDidSelectGraph(this, options_, graph_path_);
		}
		disappear();
	}
}

void GraphSelectView::disappear()
{
	qDebug() << "Disappearing \n";
	ui.graphTypeBox->setCurrentIndex(0);
	imageScene_->clear();
	imageScene_->setSceneRect(0, 0, 0, 0);
	ui.okButton->setEnabled(false);
	close();
}

void GraphSelectView::reject()
{
	// handle close action
	QMessageBox::StandardButton resBtn = QMessageBox::Yes;
	bool changes = false;
	if (changes == true) {
		resBtn = QMessageBox::question(this, "Close Graph",
			tr("Are you sure?\n"),
			QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	}
	if (resBtn == QMessageBox::Yes) {
		QDialog::reject();
	}
}