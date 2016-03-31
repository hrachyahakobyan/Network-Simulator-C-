#include "stdafx.h"
#include "networkqt.h"

NetworkQT::NetworkQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	graphSelectView_ = new GraphSelectView(this);
	broadcastSelectView_ = new BroadcastSelectView(this);
	connect(graphSelectView_, SIGNAL(finishedSelect(int, const GraphOptions&, const boost::filesystem::path&)), this, SLOT(graphSelectViewFinished(int, const GraphOptions&, const boost::filesystem::path&)));
	connect(broadcastSelectView_, SIGNAL(broadcastDialogFinishedSelect(int, const BroadcastSchemeOptions&)), this, SLOT(broadcastSchemeSelectViewFinished(int, const BroadcastSchemeOptions&)));
}

NetworkQT::~NetworkQT()
{
	delete graphSelectView_;
	delete broadcastSelectView_;
}

void NetworkQT::on_actionSimulation_triggered()
{
	qDebug() << "Action simulation \n";
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

void NetworkQT::graphSelectViewFinished(int state, const GraphOptions& options, const boost::filesystem::path& image_path)
{
	qDebug() << "Graph Select view finished with state \n" << state << "\n";
	if (state == QDialog::Accepted)
	{
		qDebug() << "type " << options.type_.c_str() << "\n";
		qDebug() << "vertices " << options.n_vertices_ << "\n";
		qDebug() << "height " << options.height_ << "\n";
		qDebug() << "dimension " << options.dim_ << "\n";
		qDebug() << "k " << options.k_ << "\n";
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
		broadcastSessionView_->exec();
	}
}

void NetworkQT::broadcastSessionViewDidFinish(int state)
{
	qDebug() << "Session view finished \n";
	delete broadcastSessionView_;
}