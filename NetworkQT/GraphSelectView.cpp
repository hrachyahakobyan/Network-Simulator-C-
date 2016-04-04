#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false), dialog_(0)
{
	ui.setupUi(this);
	ui.okButton->setDisabled(true);
	imageScene_ = new QGraphicsScene(this);
	type_mapper_.insert(std::make_pair(1, GraphBuilder::GraphOptions::GraphType::Graph_Complete));
	type_mapper_.insert(std::make_pair(2, GraphBuilder::GraphOptions::GraphType::Graph_Hypercube));
	type_mapper_.insert(std::make_pair(3, GraphBuilder::GraphOptions::GraphType::Graph_Knodel));
	type_mapper_.insert(std::make_pair(4, GraphBuilder::GraphOptions::GraphType::Graph_Grid));
	type_mapper_.insert(std::make_pair(5, GraphBuilder::GraphOptions::GraphType::Graph_Torus));
	type_mapper_.insert(std::make_pair(6, GraphBuilder::GraphOptions::GraphType::Graph_Binomial));
	type_mapper_.insert(std::make_pair(7, GraphBuilder::GraphOptions::GraphType::Graph_KTree));
	type_mapper_.insert(std::make_pair(8, GraphBuilder::GraphOptions::GraphType::Graph_Random));
	type_mapper_.insert(std::make_pair(9, GraphBuilder::GraphOptions::GraphType::Graph_CCC));
	type_mapper_.insert(std::make_pair(10, GraphBuilder::GraphOptions::GraphType::Graph_Bipartite));
	type_mapper_.insert(std::make_pair(11, GraphBuilder::GraphOptions::GraphType::Graph_Dipper));
	type_mapper_.insert(std::make_pair(12, GraphBuilder::GraphOptions::GraphType::Graph_RandomTree));
	type_mapper_.insert(std::make_pair(13, GraphBuilder::GraphOptions::GraphType::Graph_FixedRandom));
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
		connect(dialog_, SIGNAL(finishedInput(int, const GraphBuilder::GraphOptions&)), this, SLOT(inputDialogFinished(int, const GraphBuilder::GraphOptions&)));
		dialog_->exec();
	}
}


void GraphSelectView::inputDialogFinished(int status, const GraphBuilder::GraphOptions& options)
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
	ui.graphTypeBox->setCurrentIndex(0);
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

void GraphSelectView::buildInputDialog(GraphBuilder::GraphOptions::GraphType type)
{
	QList<QString> labels;
	if (type == GraphBuilder::GraphOptions::GraphType::Graph_Binomial)
	{
		labels << "Height";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Complete)
	{
		labels << "Vertices";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Hypercube)
	{
		labels << "Dimension";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Knodel)
	{
		labels << "Vertices";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_KTree)
	{
		labels << "Height";
		labels << "K";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Grid)
	{
		labels << "N";
		labels << "M";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Torus)
	{
		labels << "N";
		labels << "M";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Random)
	{
		labels << "Probability";
		labels << "Vertices";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_CCC)
	{
		labels << "Dimension";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Bipartite)
	{
		labels << "M" << "N";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_Dipper)
	{
		labels << "M" << "N";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_RandomTree)
	{
		labels << "Children" << "Height";
	}
	else if (type == GraphBuilder::GraphOptions::GraphType::Graph_FixedRandom)
	{
		labels << "Vertices";
	}
	dialog_ = new GraphOptionsInputDialog(this, labels, type);
	labels.clear();
}