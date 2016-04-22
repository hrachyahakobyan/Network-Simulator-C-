#include "stdafx.h"
#include "GraphSelectView.h"

GraphSelectView::GraphSelectView(QWidget *parent)
	: QDialog(parent), shouldSave_(false), spinDialog_(0), dialog_(0)
{
	ui.setupUi(this);
	ui.okButton->setDisabled(true);
	imageScene_ = new QGraphicsScene(this);

	inputMap_.insert(1, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Complete, QList<QString>({"Vertices"})));
	inputMap_.insert(2, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Hypercube, QList<QString>({ "Dimension" })));
	inputMap_.insert(3, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Knodel, QList<QString>({ "Vertices" })));
	inputMap_.insert(4, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Grid, QList<QString>({ "M", "N" })));
	inputMap_.insert(5, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Torus, QList<QString>({ "M", "N" })));
	inputMap_.insert(6, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Binomial, QList<QString>({ "Height" })));
	inputMap_.insert(7, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_KTree, QList<QString>({ "Height", "K" })));
	inputMap_.insert(8, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Random, QList<QString>({ "Vertices", "Probability" })));
	inputMap_.insert(9, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_CCC, QList<QString>({ "Dimension" })));
	inputMap_.insert(10, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Bipartite, QList<QString>({ "M", "N" })));
	inputMap_.insert(11, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_Dipper, QList<QString>({ "M", "N" })));
	inputMap_.insert(12, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_RandomTree, QList<QString>({ "Height", "Children" })));
	inputMap_.insert(13, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_FixedRandom, QList<QString>({ "Vertices" })));
	inputMap_.insert(14, qMakePair(GraphBuilder::GraphOptions::GraphType::Graph_ScaleFreeRandom, QList<QString>({ "New Vertices", "Kernel", "Edges" })));

	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Complete, QList<QPair<QString, QPair<int, int>>>(
	{qMakePair(QString("Vertices"), qMakePair(1, 20))}));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Hypercube, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Dimension"), qMakePair(1, 7)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Knodel, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Vertices"), qMakePair(1, 20)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Grid, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("M"), qMakePair(1, 100)), qMakePair(QString("N"), qMakePair(1, 100)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Torus, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("M"), qMakePair(1, 20)), qMakePair(QString("N"), qMakePair(1, 20)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Binomial, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Height"), qMakePair(1, 10))}));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_KTree, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Height"), qMakePair(1, 5)), qMakePair(QString("K"), qMakePair(1, 5)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Random, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Vertices"), qMakePair(1, 5000)), qMakePair(QString("Probability"), qMakePair(1, 100)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_CCC, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Dimension"), qMakePair(1, 7)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Bipartite, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("M"), qMakePair(1, 20)), qMakePair(QString("N"), qMakePair(1, 20)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_Dipper, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("M"), qMakePair(1, 20)), qMakePair(QString("N"), qMakePair(1, 20)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_RandomTree, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Height"), qMakePair(1, 5)), qMakePair(QString("Children"), qMakePair(1, 5)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_FixedRandom, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("Vertices"), qMakePair(1, 200)) }));
	spinBoxMap_.insert(GraphBuilder::GraphOptions::GraphType::Graph_ScaleFreeRandom, QList<QPair<QString, QPair<int, int>>>(
	{ qMakePair(QString("New Vertices"), qMakePair(1, 1000)), qMakePair(QString("Kernel"), qMakePair(1, 1000)), qMakePair(QString("Edges"), qMakePair(1, 1000))}));
}

GraphSelectView::~GraphSelectView()
{
	imageScene_->clear();
	delete imageScene_;
	if (dialog_ != 0)
		delete dialog_;
	if (spinDialog_ != 0)
		delete spinDialog_;
}

void GraphSelectView::on_graphTypeBox_currentIndexChanged(QString s)
{
	qDebug() << "GraphSelectView: graphTypeBox index changed";
	qDebug() << s;
	qDebug() << "\n";
	int index = ui.graphTypeBox->currentIndex();
	if (index != 0)
	{	
		buildSpinDialog(inputMap_[index].first);
		connect(spinDialog_, SIGNAL(multiSpinboxDialogDidFinish(int, const QMap<QString, int>&)), this, SLOT(spinDialogDidFinish(int, const QMap<QString, int>&)));
		spinDialog_->exec();
	}
}


void GraphSelectView::spinDialogDidFinish(int status, const QMap<QString, int>& input)
{
	qDebug() << " Spin dialog finished with state " << status << "\n";
	if (status == QDialog::Accepted)
	{
		parseInput(input, options_);
		options_.type_ = inputMap_[ui.graphTypeBox->currentIndex()].first;
		GraphManager::sharedManager()->graphImageWithOptions(options_, graph_path_, folder_path_);
		image_.load(graph_path_.string().c_str());
		imageScene_->clear();
		imageScene_->addPixmap(image_);
		imageScene_->setSceneRect(image_.rect());
		ui.graphicsView->setScene(imageScene_);
		ui.okButton->setEnabled(true);
	}
	delete spinDialog_;
	spinDialog_ = 0;
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
	imageScene_->clear();
	imageScene_->setSceneRect(0, 0, 0, 0);
	ui.okButton->setEnabled(false);
	ui.graphTypeBox->setCurrentIndex(0);
	QDialog::reject();
	Q_EMIT finishedSelect(QDialog::Rejected, options_, graph_path_);
}

void GraphSelectView::accept()
{
	imageScene_->clear();
	imageScene_->setSceneRect(0, 0, 0, 0);
	ui.okButton->setEnabled(false);
	ui.graphTypeBox->setCurrentIndex(0);
	QDialog::accept();
	Q_EMIT finishedSelect(QDialog::Accepted, options_, graph_path_);
}


void GraphSelectView::buildSpinDialog(GraphBuilder::GraphOptions::GraphType type)
{
	spinDialog_ = new MultiSpinboxDialog(this, spinBoxMap_[type]);
}

void GraphSelectView::parseInput(const QMap<QString, int>& inputs_map_, GraphBuilder::GraphOptions& options)
{
	if (inputs_map_.find("Height") != inputs_map_.end())
		options_.height_ = inputs_map_["Height"];
	if (inputs_map_.find("K") != inputs_map_.end())
		options_.k_ = inputs_map_["K"];
	if (inputs_map_.find("Vertices") != inputs_map_.end())
		options_.n_vertices_ = inputs_map_["Vertices"];
	if (inputs_map_.find("Dimension") != inputs_map_.end())
		options_.dim_ = inputs_map_["Dimension"];
	if (inputs_map_.find("M") != inputs_map_.end())
		options_.m_ = inputs_map_["M"];
	if (inputs_map_.find("N") != inputs_map_.end())
		options_.n_ = inputs_map_["N"];
	if (inputs_map_.find("Probability") != inputs_map_.end())
		options_.p_ = inputs_map_["Probability"];
	if (inputs_map_.find("Children") != inputs_map_.end())
		options_.children_ = inputs_map_["Children"];
	if (inputs_map_.find("New Vertices") != inputs_map_.end())
		options_.n_ = inputs_map_["New Vertices"];
	if (inputs_map_.find("Kernel") != inputs_map_.end())
		options_.m_ = inputs_map_["Kernel"];
	if (inputs_map_.find("Edges") != inputs_map_.end())
		options_.k_ = inputs_map_["Edges"];
}

