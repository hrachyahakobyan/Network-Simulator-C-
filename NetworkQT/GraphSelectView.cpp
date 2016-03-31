#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false), dialog_(0)
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
	if (dialog_ != 0)
		delete dialog_;
}

void GraphSelectView::on_graphTypeBox_currentIndexChanged(QString s)
{
	qDebug() << "GraphSelectView: graphTypeBox index changed";
	qDebug() << s;
	qDebug() << "\n";
	int index = ui.graphTypeBox->currentIndex();
	if (index != 0)
	{	
		buildInputDialog(type_mapper_.at(index));
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
	dialog_ = 0;
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
		if (dir.size() > 0)
		{
			GraphManager::sharedManager()->saveGraphImage(folder_path_, dest_path);
			accept();
		}
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
	imageScene_->clear();
	imageScene_->setSceneRect(0, 0, 0, 0);
	ui.okButton->setEnabled(false);
	ui.graphTypeBox->setCurrentIndex(0);
	Q_EMIT finishedSelect(QDialog::Rejected, options_, graph_path_);
}

void GraphSelectView::accept()
{
	QDialog::accept();
	imageScene_->clear();
	imageScene_->setSceneRect(0, 0, 0, 0);
	ui.okButton->setEnabled(false);
	ui.graphTypeBox->setCurrentIndex(0);
	Q_EMIT finishedSelect(QDialog::Accepted, options_, graph_path_);
}

void GraphSelectView::buildInputDialog(const std::string& type)
{
	QList<QString> labels;
	if (type.compare(GRAPH_BINOMIAL) == 0)
	{
		labels << "Height";
	}
	else if (type.compare(GRAPH_COMPLETE) == 0)
	{
		labels << "Vertices";
	}
	else if (type.compare(GRAPH_HYPER) == 0)
	{
		labels << "Dimension";
	}
	else if (type.compare(GRAPH_KNODEL) == 0)
	{
		labels << "Vertices";
	}
	else if (type.compare(GRAPH_KTREE) == 0)
	{
		labels << "Height";
		labels << "K";
	}
	dialog_ = new GraphOptionsInputDialog(this, labels, type);
}