#include "stdafx.h"
#include "networkqt.h"

NetworkQT::NetworkQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	graphSelectView_ = new GraphSelectView(this);
	graphSelectView_->hide();
}

NetworkQT::~NetworkQT()
{
	
}

void NetworkQT::on_pushButton_clicked()
{
	qDebug() << "Push button clicked\n";
}


void NetworkQT::on_actionSimulation_triggered()
{
	qDebug() << "Action simulation \n";
}


void NetworkQT::on_actionGraph_triggered()
{
	qDebug() << "Action graph\n";
	graphSelectView_->show();
}

void NetworkQT::on_actionExit_triggered()
{
	qDebug() << "Action exit\n";
	QCoreApplication::exit();
}

void NetworkQT::graphSelectViewDidSaveGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path)
{

}

void NetworkQT::graphSelectViewDidSelectGraph(GraphSelectView* view, const GraphOptions& options, const boost::filesystem::path& image_path)
{

}