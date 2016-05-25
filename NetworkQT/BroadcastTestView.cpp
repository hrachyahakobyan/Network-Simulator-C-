#include "stdafx.h"
#include "BroadcastTestView.h"

BroadcastTestView::BroadcastTestView(QWidget *parent)
	: QDialog(parent), broadcastView_(0), graphView_(0), testThread_(0)
{
	ui.setupUi(this);

	graphView_ = new GraphSelectView(this);
	broadcastView_ = new BroadcastSelectView(this);
	testThread_ = new BroadcastTestThread;

	connect(ui.iterationSpinBox, SIGNAL(valueChanged(const QString&)), this, SLOT(onIterationCountSpinBoxValueChanged(const QString&)));
	connect(graphView_, SIGNAL(finishedSelect(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)), this, SLOT(on_graphSelectViewFinished(int, const GraphBuilder::GraphOptions&, const boost::filesystem::path&)));
	connect(broadcastView_, SIGNAL(broadcastDialogFinishedSelect(int, const BroadcastSchemeOptions&)), this, SLOT(on_broadcastSelectViewFinished(int, const BroadcastSchemeOptions&)));
	connect(testThread_, SIGNAL(broadcastThreadDidUpdate(int, double, bool, QString)), this, SLOT(on_broadcastTestDidUpdate(int, double, bool, QString)));
	connect(testThread_, SIGNAL(finished()), this, SLOT(on_broadcastTestDidFinish()));

	ui.iterationSpinBox->setMaximum(1000);
	ui.iterationSpinBox->setMinimum(1);
	ui.iterationSpinBox->setValue(1);

	ui.testProgressBar->setMinimum(1);
	ui.testProgressBar->setMaximum(1);
	ui.testProgressBar->setValue(0);

	ui.timeLabel->setText(QString(""));

	ui.cancelButton->setEnabled(false);
	ui.saveButton->setEnabled(false);
}

BroadcastTestView::~BroadcastTestView()
{
	if (broadcastView_ != 0)
		delete broadcastView_;
	if (graphView_ != 0)
		delete graphView_;
	if (testThread_ != 0)
		delete testThread_;
}

void BroadcastTestView::on_broadcastTestDidUpdate(int it, double t, bool f, QString filename)
{
	qDebug() << "It " << it << " time " << t << " finished " << f <<  '\n';
	t = t / 1000000;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << t;
	QString timeText(stream.str().c_str());
	timeText.append(" s");
	ui.timeLabel->setText(timeText);
	ui.testProgressBar->setValue(it);
	if (f)
	{
		ui.timeLabel->setText(QString(""));
		ui.testProgressBar->setValue(1);
		ui.startButton->setEnabled(true);
		ui.cancelButton->setEnabled(false);
		statPath_ = boost::filesystem::path(filename.toStdString());
		if (statPath_.empty())
			ui.saveButton->setEnabled(false);
		else
			ui.saveButton->setEnabled(true);
	}
}

void BroadcastTestView::on_broadcastTestDidFinish()
{

}

void BroadcastTestView::reject()
{
	if (testThread_->isRunning())
	{
		QMessageBox msg;
		msg.setText("Test running");
		msg.exec();
	}
	else
	{
		QDialog::reject();
	}
}

void BroadcastTestView::onIterationCountSpinBoxValueChanged(const QString& text)
{
	int iter = text.toInt();
	if (iter < 1)
	{
		iter = 1;
		ui.iterationSpinBox->setValue(1);
	}
	TestOptions op;
	op.iterCount_ = iter;
	testThread_->setTestOptions(op);
	ui.testProgressBar->setMaximum(iter);
	ui.testProgressBar->setValue(0);
}

void BroadcastTestView::on_startButton_clicked()
{
	if (testThread_->isRunning() == false)
	{
		ui.testProgressBar->setValue(0);
		ui.cancelButton->setEnabled(true);
		ui.startButton->setEnabled(false);
		ui.saveButton->setEnabled(false);
		testThread_->start();
	}
}

void BroadcastTestView::on_cancelButton_clicked()
{
	if (testThread_->isRunning() == true)
	{
		testThread_->cancel();
		ui.testProgressBar->setValue(0);
		ui.timeLabel->setText(QString(""));
		ui.cancelButton->setEnabled(false);
		ui.startButton->setEnabled(true);
		ui.saveButton->setEnabled(false);
	}
}

void BroadcastTestView::on_saveButton_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Choose folder"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	boost::filesystem::path dest_path(dir.toLocal8Bit().constData());
	if (dir.size() > 0)
	{
		std::string date = TimeManager::sharedTimeManager()->date_string();
		dest_path.append("/");
		date.append("-stat");
		dest_path.append(date.c_str());
		FileManager::sharedManager()->copy_dir(statPath_, dest_path);
	}
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
		testThread_->setGraphOptions(options);
		ui.graphLabel->setText(QString(options.graphType().c_str()));
	}
}

void BroadcastTestView::on_broadcastSelectViewFinished(int state, const BroadcastSchemeOptions& options)
{
	if (state == QDialog::Accepted)
	{
		testThread_->setSchemeOptions(options);
		ui.broadcastLabel->setText(QString(options.send_type_.c_str()));
	}
}
