#include "stdafx.h"
#include "SessionView.h"

SessionView::SessionView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
}

SessionView::SessionView(QWidget* parent, std::unique_ptr<Session> session)
	: QDialog(parent), session_(std::move(session))
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);

	allowedStates_ = (*session_).allowedStates();
	for (auto it = allowedStates_.begin(); it != allowedStates_.end(); ++it)
	{
		ui.addVertextStateComboBox->addItem(QString((*it).first.c_str()));
		ui.changeStateComboBox->addItem(QString((*it).first.c_str()));
	}
	updateSpinBoxes();
	ui.renderCheckBox->setCheckState(Qt::CheckState::Checked);
	draw((*session_).last());
	initializeGraphView();
	ui.tickSpinBox->setMinimum(1);
}

SessionView::~SessionView()
{
	session_.reset();
	imageScene_->clear();
	delete imageScene_;
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
		QPen pen;
		pen.setColor(convert(color));
		pen.setWidth(5);
		ui.graphPlotView->graph(index)->setPen(pen);
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


void SessionView::on_lastButton_clicked()
{
	qDebug() << "SessionView last button clicked \n";
	draw((*session_).last());
}


void SessionView::on_resetButton_clicked()
{
	(*session_).reset();
	draw((*session_).last());
	ui.renderCheckBox->setCheckState(Qt::CheckState::Checked);
	updatePlot();
	updateSpinBoxes();
}

void SessionView::on_renderCheckBox_stateChanged(int s)
{
	qDebug() << "SessionView changed render state " << s << "\n";
	(*session_).shouldRender = s == Qt::CheckState::Checked ? true : false;
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
	if (ui.renderCheckBox->checkState() == Qt::CheckState::Checked)
	{
		image_.load(img.string().c_str());
		imageScene_->clear();
		imageScene_->addPixmap(image_);
		imageScene_->setSceneRect(image_.rect());
		ui.graphicsView->setScene(imageScene_);
	}
}

void SessionView::updateSpinBoxes()
{
	int vertexCount = (*session_).vertexCount() - 1;
	ui.changeStateSpinbox->setMinimum(0);
	ui.changeStateSpinbox->setMaximum(vertexCount);
	ui.sourceSpinbox->setMinimum(0);
	ui.sourceSpinbox->setMaximum(vertexCount);
	ui.targetSpinbox->setMinimum(0);
	ui.targetSpinbox->setMaximum(vertexCount);
	ui.removeVertexSpinbox->setMinimum(0);
	ui.removeVertexSpinbox->setMaximum(vertexCount);
}

/*Edit actions*/
void SessionView::on_changeStateButton_clicked()
{
	editAction_.type_ = GraphEditAction::EditType::SetState;
	editAction_.v_ = ui.changeStateSpinbox->value();
	editAction_.state_ = allowedStates_[ui.changeStateComboBox->currentText().toStdString()];
	edit();
}

void SessionView::on_addEdgeButton_clicked()
{
	editAction_.type_ = GraphEditAction::EditType::AddEdge;
	editAction_.src_ = ui.sourceSpinbox->value();
	editAction_.targ_ = ui.targetSpinbox->value();
	edit();
}

void SessionView::on_removeEdgeButton_clicked()
{
	editAction_.type_ = GraphEditAction::EditType::DeleteEdge;
	editAction_.src_ = ui.sourceSpinbox->value();
	editAction_.targ_ = ui.targetSpinbox->value();
	edit();
}

void SessionView::on_addVertexButton_clicked()
{
	editAction_.type_ = GraphEditAction::EditType::AddVertex;
	editAction_.state_ = allowedStates_[ui.addVertextStateComboBox->currentText().toStdString()];
	edit();
}

void SessionView::on_removeVertexButton_clicked()
{
	editAction_.type_ = GraphEditAction::EditType::DeleteVertex;
	editAction_.v_ = ui.removeVertexSpinbox->value();
	edit();
}

void SessionView::edit()
{
	(*session_).edit(editAction_);
	draw((*session_).last());
	updateSpinBoxes();
}
