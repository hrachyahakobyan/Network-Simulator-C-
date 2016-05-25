#include "stdafx.h"
#include "BroadcastTestView.h"

BroadcastTestView::BroadcastTestView(QWidget *parent)
	: QDialog(parent), broadcastView_(0), graphView_(0)
{
	ui.setupUi(this);

	graphView_ = new GraphSelectView(this);
	broadcastView_ = new BroadcastSelectView(this);

	connect(ui.iterationSpinBox, SIGNAL(valueChanged(const QString&)), this, SLOT(onIterationCountSpinBoxValueChanged(const QString&)));
	connect(graphView_, SIGNAL(finishedSelect(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)), this, SLOT(on_graphSelectViewFinished(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)));
	connect(broadcastView_, SIGNAL(broadcastDialogFinishedSelect(int, const BroadcastSchemeOptions&)), this, SLOT(on_broadcastSelectViewFinished(int, const BroadcastSchemeOptions&)));

	ui.iterationSpinBox->setMaximum(1000);
	ui.iterationSpinBox->setMinimum(1);
	ui.iterationSpinBox->setValue(1);

	schemeOp_ = BroadcastSchemeOptions(SEND_SCHEME_M1, RECEIVE_SCHEME_M, FINISH_SCHEME_M);
	graphOp_ = GraphBuilder::GraphOptions();
	graphOp_.type_ = GraphBuilder::GraphOptions::GraphType::Graph_Complete;
	graphOp_.n_vertices_ = 10;
	testOp_ = TestOptions();
	testOp_.iterCount_ = 1;

	ui.testProgressBar->setMinimum(1);
	ui.testProgressBar->setMaximum(testOp_.iterCount_);
	ui.testProgressBar->setValue(0);
}

BroadcastTestView::~BroadcastTestView()
{
	if (broadcastView_ != 0)
		delete broadcastView_;
	if (graphView_ != 0)
		delete graphView_;
}


void BroadcastTestView::onIterationCountSpinBoxValueChanged(const QString& text)
{
	testOp_.iterCount_ = ui.iterationSpinBox->value();
	ui.testProgressBar->setMaximum(testOp_.iterCount_);
}

void BroadcastTestView::on_startButton_clicked()
{
	broadTest_.test(graphOp_, schemeOp_, testOp_);
}

void BroadcastTestView::on_cancelButton_clicked()
{

}

void BroadcastTestView::on_saveButton_clicked()
{
	
}

void BroadcastTestView::on_broadcastButton_clicked()
{
	qDebug() << "Broadcast select \n";
	broadcastView_->exec();
}

void BroadcastTestView::on_graphButton_clicked()
{
	qDebug() << "Graph select \n";
	graphView_->exec();
}

void BroadcastTestView::on_graphSelectViewFinished(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& path)
{
	if (state == QDialog::Accepted)
	{
		graphOp_ = options; 
		ui.graphLabel->setText(QString(options.graphType().c_str()));
	}
}

void BroadcastTestView::on_broadcastSelectViewFinished(int state, const BroadcastSchemeOptions& options)
{
	if (state == QDialog::Accepted)
	{
		schemeOp_ = options;
		ui.broadcastLabel->setText(QString(options.send_type_.c_str()));
	}
}
