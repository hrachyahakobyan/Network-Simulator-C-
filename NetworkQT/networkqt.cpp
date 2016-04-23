#include "stdafx.h"
#include "networkqt.h"
#include "CleanUp.h"
#include "HNABroadcastSession.h"
#include "DiseaseSession.h"


NetworkQT::NetworkQT(QWidget *parent)
	: QMainWindow(parent), sessionView_(0),
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
	if (sessionView_ != 0)
		delete sessionView_;
	if (diseaseSelectView_ != 0)
		delete diseaseSelectView_;
}

void NetworkQT::on_actionBroadcasting_triggered()
{
	qDebug() << "Action Broadcasting \n";
	sim_ = Simulation::Broadcast;
	graphSelectView_->shouldSave_ = false;
	graphSelectView_->exec();
}


void NetworkQT::on_actionDiseaseModel_triggered()
{ 
	qDebug() << "Action disease model \n";
	sim_ = Simulation::Disease;
	graphSelectView_->shouldSave_ = false;
	graphSelectView_->exec();
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
			switch (sim_)
			{
			case Simulation::Broadcast:
				broadcastSelectView_->exec();
				break;
			case Simulation::Disease:
				diseaseSelectView_->exec();
				break;
			}
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
		sessionView_ = new SessionView(this, std::move(session));
		connect(sessionView_, SIGNAL(sessionViewDidFinish(int)), this, SLOT(sessionViewDidFinish(int)));
		sessionView_->exec();
	}
}

void NetworkQT::sessionViewDidFinish(int state)
{
	qDebug() << "Session view finished \n";
	delete sessionView_;
	sessionView_ = 0;
}

void NetworkQT::diseaseSelectViewDidFinish(int state, const DiseaseSimulation::DiseaseOptions& options)
{
	qDebug() << "DiseaseSelectView did finish with state " << state << "\n";
	if (state == QDialog::Accepted)
	{
		d_op_ = options;
		std::unique_ptr<DiseaseSession> session = DiseaseSession::session(g_op_, d_op_);
		sessionView_ = new SessionView(this, std::move(session));
		connect(sessionView_, SIGNAL(sessionViewDidFinish(int)), this, SLOT(sessionViewDidFinish(int)));
		sessionView_->exec();
	}
}