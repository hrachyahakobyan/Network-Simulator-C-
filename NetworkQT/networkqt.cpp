#include "stdafx.h"
#include "networkqt.h"
#include "CleanUp.h"
#include "DiseaseFactory.h"


NetworkQT::NetworkQT(QWidget *parent)
	: QMainWindow(parent), broadcastSessionView_(0),
	  broadcastSelectView_(0), graphSelectView_(0),
	  diseaseSelectView_(0)
{
	ui.setupUi(this);
	graphSelectView_ = new GraphSelectView(this);
	broadcastSelectView_ = new BroadcastSelectView(this);
	diseaseSelectView_ = new DiseaseSelectView(this);
	connect(graphSelectView_, SIGNAL(finishedSelect(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)), this, SLOT(graphSelectViewFinished(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)));
	connect(broadcastSelectView_, SIGNAL(broadcastDialogFinishedSelect(int, const BroadcastSchemeOptions&)), this, SLOT(broadcastSchemeSelectViewFinished(int, const BroadcastSchemeOptions&)));
	connect(diseaseSelectView_, SIGNAL(diseaseSelectViewFinished(int, const DiseaseSimulation::DiseaseOptions&)), this, SLOT(diseaseSelectViewDidFinish(int, const DiseaseSimulation::DiseaseOptions&)));
	this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
}

NetworkQT::~NetworkQT()
{
	CleanUp::cleanUp();
	if (graphSelectView_ != 0)
		delete graphSelectView_;
	if (broadcastSelectView_ != 0)
		delete broadcastSelectView_;
	if (broadcastSessionView_ != 0)
		delete broadcastSessionView_;
	if (diseaseSelectView_ != 0)
		delete diseaseSelectView_;
}

void NetworkQT::on_actionBroadcasting_triggered()
{
	qDebug() << "Action Broadcasting \n";
	graphSelectView_->shouldSave_ = false;
	graphSelectView_->exec();
}


void NetworkQT::on_actionDiseaseModel_triggered()
{ 
	qDebug() << "Action disease model \n";
	diseaseSelectView_->exec();
}

void NetworkQT::on_actionGraph_triggered()
{
	qDebug() << "Action graph\n";
	graphSelectView_->shouldSave_ = true;
	graphSelectView_->exec();
}

void NetworkQT::on_actionExit_triggered()
{
	qDebug() << "Action exit\n";
	QCoreApplication::exit();
}

void NetworkQT::graphSelectViewFinished(int state, const GraphBuilder::GraphOptions& options, const boost::filesystem::path& image_path)
{
	qDebug() << "Graph Select view finished with state \n" << state << "\n";
	if (state == QDialog::Accepted)
	{
		qDebug() << "vertices " << options.n_vertices_ << "\n";
		qDebug() << "height " << options.height_ << "\n";
		qDebug() << "dimension " << options.dim_ << "\n";
		g_op_ = options;
		if (graphSelectView_->shouldSave_ == false)
		{
			broadcastSelectView_->exec();
		}
	}
}

void NetworkQT::broadcastSchemeSelectViewFinished(int state, const BroadcastSchemeOptions& options)
{
	qDebug() << "Broadcast select view finished with state " << state << "\n";
	if (state == QDialog::Accepted)
	{
		s_op_ = options;
		std::unique_ptr<HNABroadcastSession> session = HNABroadcastSession::session(g_op_, s_op_);
		broadcastSessionView_ = new BroadcastSessionView(this, std::move(session));
		connect(broadcastSessionView_, SIGNAL(sessionViewDidFinish(int)), this, SLOT(broadcastSessionViewDidFinish(int)));
		broadcastSessionView_->exec();
	}
}

void NetworkQT::broadcastSessionViewDidFinish(int state)
{
	qDebug() << "Session view finished \n";
	delete broadcastSessionView_;
	broadcastSessionView_ = 0;
}

void NetworkQT::diseaseSelectViewDidFinish(int state, const DiseaseSimulation::DiseaseOptions& options)
{
	qDebug() << "DiseaseSelectView did finish with state " << state << "\n";
	if (state == QDialog::Accepted)
	{

	}
}