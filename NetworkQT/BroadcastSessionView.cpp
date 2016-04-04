#include "stdafx.h"
#include "BroadcastSessionView.h"

BroadcastSessionView::BroadcastSessionView(QWidget *parent)
	: QDialog(parent), editDialog_(0)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
}

BroadcastSessionView::BroadcastSessionView(QWidget* parent, std::unique_ptr<HNABroadcastSession> session)
	: QDialog(parent), session_(std::move(session)), editDialog_(0)
{
	ui.setupUi(this);
	ui.tickSpinBox->setValue(1);
	imageScene_ = new QGraphicsScene(this);
	draw((*session_).last());
}

BroadcastSessionView::~BroadcastSessionView()
{
	session_.reset();
	imageScene_->clear();
	delete imageScene_;
	if (editDialog_ != 0)
		delete editDialog_;
}

void BroadcastSessionView::on_saveButton_clicked()
{
	qDebug() << "BroadcastView save button clicked \n";
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

void BroadcastSessionView::on_tickButton_clicked()
{
	qDebug() << "BroadcastView tick button clicked \n";
	(*session_).tick(ui.tickSpinBox->value());
	draw((*session_).last());
}

void BroadcastSessionView::on_finishButton_clicked()
{
	qDebug() << "BroadcastView finish button clicked \n";
	if (!(*session_).finish())
	{
		QMessageBox msg;
		msg.setText("Failed to finish in 100 steps");
		msg.exec();
	}
	draw((*session_).last());
}

void BroadcastSessionView::on_redrawButton_clicked()
{
	boost::filesystem::path p = (*session_).redraw();
	if (p.empty() == false)
		draw(p);
}

void BroadcastSessionView::on_nextButton_clicked()
{
	qDebug() << "BroadcastView next button clicked \n";
	draw((*session_).next());
}

void BroadcastSessionView::on_previousButton_clicked()
{
	qDebug() << "BroadcastView prev button clicked \n";
	draw((*session_).previous());
}

void BroadcastSessionView::on_editTypeBox_currentIndexChanged(QString s)
{
	if (ui.editTypeBox->currentIndex() != 0)
	{
		buildEditInputDialog();
	}
}


void BroadcastSessionView::on_tickSpinBox_valueChanged(int v)
{
	if (v < 1)
	{
		ui.tickSpinBox->setValue(1);
	}
}

void BroadcastSessionView::accept()
{
	QDialog::accept();
	Q_EMIT sessionViewDidFinish(QDialog::Accepted);
}

void BroadcastSessionView::reject()
{
	QDialog::reject();
	Q_EMIT sessionViewDidFinish(QDialog::Rejected);
}

void BroadcastSessionView::draw(const boost::filesystem::path& img)
{
	image_.load(img.string().c_str());
	imageScene_->clear();
	imageScene_->addPixmap(image_);
	imageScene_->setSceneRect(image_.rect());
	ui.graphicsView->setScene(imageScene_);
}

void BroadcastSessionView::buildEditInputDialog()
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


void BroadcastSessionView::editDialogDidFinish(int state, const GraphEditAction& action)
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