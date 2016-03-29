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
	imageScene_->clear();
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
		dialog_ = new GraphOptionsInputDialog(this, type_mapper_.at(index));
		connect(dialog_, SIGNAL(finishedInput(int, const GraphOptions&)), this, SLOT(inputDialogFinished(int, const GraphOptions&)));
		dialog_->exec();
	}
}


void GraphSelectView::inputDialogFinished(int status, const GraphOptions& options)
{
	if (status == QDialog::Accepted)
	{
		options_ = options;
		GraphManager::sharedManager()->graphImageWithOptions(options_, graph_path_, folder_path_);
		image_.load(graph_path_.string().c_str());
		imageScene_->clear();
		imageScene_->addPixmap(image_);
		imageScene_->setSceneRect(image_.rect());
		ui.graphicsView->setScene(imageScene_);
		ui.okButton->setEnabled(true);
	}
	delete dialog_;
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
		accept();
	}
	else
	{
		qDebug() << "GraphSelectView: selected graph \n";
		accept();
	}
}

void GraphSelectView::reject()
{
	QDialog::reject();
	Q_EMIT finishedSelect(QDialog::Rejected, options_, graph_path_);
}

void GraphSelectView::accept()
{
	QDialog::accept();
	Q_EMIT finishedSelect(QDialog::Accepted, options_, graph_path_);
}