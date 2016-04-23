#include "stdafx.h"
#include "SessionView.h"

SessionView::SessionView(QWidget *parent)
	: QDialog(parent), editDialog_(0)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
}

SessionView::SessionView(QWidget* parent, std::unique_ptr<Session> session)
	: QDialog(parent), session_(std::move(session)), editDialog_(0)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
	draw((*session_).last());
	initializeGraphView();
}

SessionView::~SessionView()
{
	session_.reset();
	imageScene_->clear();
	delete imageScene_;
	if (editDialog_ != 0)
		delete editDialog_;
}

void SessionView::initializeGraphView()
{
	std::map<std::string, std::pair<Color, std::vector<int>>> data = (*session_).data();
	auto it = data.begin();
	for (it = data.begin(); it != data.end(); ++it)
	{
		ui.graphPlotView->addGraph();
		int graphCount = ui.graphPlotView->graphCount();
		int index = graphCount - 1;
		plotIndexMap_[(*it).first] = index;
		Color color = (*it).second.first;
		ui.graphPlotView->graph(index)->setPen(QPen(convert(color)));
		ui.graphPlotView->graph(index)->setName(QString((*it).first.c_str()));
	}
	QFont axisFont = font();
	axisFont.setPointSize(12);
	ui.graphPlotView->xAxis->setLabel(QString("Time"));
	ui.graphPlotView->yAxis->setLabel(QString("Nodes"));
	ui.graphPlotView->xAxis->setLabelFont(axisFont);
	ui.graphPlotView->yAxis->setLabelFont(axisFont);
	ui.graphPlotView->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	ui.graphPlotView->legend->setVisible(true);
	QFont legendFont = font();
	legendFont.setPointSize(9);
	ui.graphPlotView->legend->setFont(legendFont);
	ui.graphPlotView->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
	updatePlot();
	ui.graphPlotView->xAxis->setRangeLower(0);
	ui.graphPlotView->yAxis->setRangeLower(0);
	ui.graphPlotView->plotLayout()->insertRow(0);
	ui.graphPlotView->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui.graphPlotView, (*session_).description().c_str()));
}

void SessionView::updatePlot()
{
	std::map<std::string, std::pair<Color, std::vector<int>>> data = (*session_).data();
	auto it = data.begin();
	QVector<double> xAxis((*it).second.second.size());
	for (int i = 1; i < xAxis.size(); i++)
	{
		xAxis[i] = i;
	}
	for (it = data.begin(); it != data.end(); ++it)
	{
		QVector<double> data = QVector<double>::fromStdVector(std::vector<double>((*it).second.second.begin(), (*it).second.second.end()));
		int index = plotIndexMap_[(*it).first];
		ui.graphPlotView->graph(index)->setData(xAxis, data);
	}
	ui.graphPlotView->rescaleAxes();
	ui.graphPlotView->replot();
}

Qt::GlobalColor SessionView::convert(Color color)
{
	switch (color)
	{
	case Color::Black:
		return Qt::black;
			break;
	case Color::Blue:
		return Qt::blue;
			break;
	case Color::Green:
		return Qt::green;
			break;
	case Color::Red:
		return Qt::red;
			break;
	case Color::White:
		return Qt::white;
			break;
		default:
			return Qt::black;
			break;
	}
}

void SessionView::on_saveButton_clicked()
{
	qDebug() << "SessionView save button clicked \n";
	QString dir = QFileDialog::getExistingDirectory(this, tr("Choose folder"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	boost::filesystem::path dest_path(dir.toLocal8Bit().constData());
	if (dir.size() > 0)
	{
		(*session_).save(dest_path);
	}
}

void SessionView::on_tickButton_clicked()
{
	qDebug() << "SessionView tick button clicked \n";
	if (!(*session_).tick(ui.tickSpinBox->value()))
		updatePlot();
	draw((*session_).last());
	std::map<std::string, std::pair<Color, std::vector<int>>> data = (*session_).data();
}

void SessionView::on_finishButton_clicked()
{
	qDebug() << "SessionView finish button clicked \n";
	if (!(*session_).finish())
	{
		QMessageBox msg;
		msg.setText("Failed to finish in 100 steps");
		msg.exec();
	}
	updatePlot();
	draw((*session_).last());
}

void SessionView::on_redrawButton_clicked()
{
	boost::filesystem::path p = (*session_).redraw();
	if (p.empty() == false)
		draw(p);
}

void SessionView::on_nextButton_clicked()
{
	qDebug() << "SessionView next button clicked \n";
	draw((*session_).next());
}

void SessionView::on_previousButton_clicked()
{
	qDebug() << "SessionView prev button clicked \n";
	draw((*session_).previous());
}

void SessionView::on_editTypeBox_currentIndexChanged(QString s)
{
	if (ui.editTypeBox->currentIndex() != 0)
	{
		buildEditInputDialog();
	}
}

void SessionView::on_resetButton_clicked()
{
	(*session_).reset();
	draw((*session_).last());
	updatePlot();
}

void SessionView::on_tickSpinBox_valueChanged(int v)
{
	if (v < 1)
	{
		ui.tickSpinBox->setValue(1);
	}
}

void SessionView::accept()
{
	QDialog::accept();
	Q_EMIT sessionViewDidFinish(QDialog::Accepted);
}

void SessionView::reject()
{
	QDialog::reject();
	Q_EMIT sessionViewDidFinish(QDialog::Rejected);
}

void SessionView::draw(const boost::filesystem::path& img)
{
	image_.load(img.string().c_str());
	imageScene_->clear();
	imageScene_->addPixmap(image_);
	imageScene_->setSceneRect(image_.rect());
	ui.graphicsView->setScene(imageScene_);
}

void SessionView::buildEditInputDialog()
{
	if (ui.editTypeBox->currentIndex() != 0)
	{
		GraphEditAction::EditType type = GraphEditAction::EditType(ui.editTypeBox->currentIndex() - 1);
		QList<QString> labels;
		if (type == GraphEditAction::EditType::AddEdge || type == GraphEditAction::EditType::DeleteEdge)
		{
			labels << "Source" << "Target";
		}
		else if (type == GraphEditAction::EditType::SetState)
		{
			labels << "State" << "Vertex";
		}
		else if (type == GraphEditAction::EditType::AddVertex)
		{
			labels << "State";
		}
		else
		{
			labels << "Vertex";
		}
		editDialog_ = new BroadcastSessionEditInputDialog(this, labels, type);
		connect(editDialog_, SIGNAL(editDialogDidFinish(int, const GraphEditAction&)), this, SLOT(editDialogDidFinish(int, const GraphEditAction&)));
		editDialog_->exec();
	}
}


void SessionView::editDialogDidFinish(int state, const GraphEditAction& action)
{
	qDebug() << "Graph edit input finished with state " << state << "\n";
	if (state == QDialog::Accepted)
	{
		(*session_).edit(action);
		draw((*session_).last());
	}
	ui.editTypeBox->setCurrentIndex(0);
	delete editDialog_;
	editDialog_ = 0;
}