#include "stdafx.h"
#include "DiseaseSelectView.h"

DiseaseSelectView::DiseaseSelectView(QWidget *parent)
	: QDialog(parent), paramSelectView_(0)
{
	ui.setupUi(this);
	ui.nextButton->setEnabled(false);
	paramSelectView_ = new DiseaseParamSelectView(this);
	connect(paramSelectView_, SIGNAL(diseaseParamSelectViewFinished(int, const DiseaseSimulation::DiseaseOptions&)), this, SLOT(on_diseaseParamSelectViewFinished(int, const DiseaseSimulation::DiseaseOptions&)));
	diseaseTypeMap_.insert("SIR", DiseaseSimulation::ModelType::SIR);
	diseaseTypeMap_.insert("SIS", DiseaseSimulation::ModelType::SIS);
	diseaseTypeMap_.insert("SIRS", DiseaseSimulation::ModelType::SIRS);
}

DiseaseSelectView::~DiseaseSelectView()
{
	if (paramSelectView_ != 0)
		delete paramSelectView_;
}

void DiseaseSelectView::on_diseaseComboBox_currentIndexChanged(QString s)
{
	qDebug() << "DiseaseSelectView: changed index \n";
	int index = ui.diseaseComboBox->currentIndex();
	if (index != 0)
	{
		options_.type = diseaseTypeMap_[ui.diseaseComboBox->currentText()];
		ui.nextButton->setEnabled(true);
	}
	else
	{
		ui.nextButton->setEnabled(false);
	}
}

void DiseaseSelectView::on_nextButton_clicked()
{
	paramSelectView_->updateModelType(options_.type);
	paramSelectView_->exec();
}

void DiseaseSelectView::accept()
{
	QDialog::accept();
	ui.nextButton->setEnabled(false);
	ui.diseaseComboBox->setCurrentIndex(0);
	Q_EMIT diseaseSelectViewFinished(QDialog::Accepted, options_);
}

void DiseaseSelectView::reject()
{
	QDialog::reject();
	ui.nextButton->setEnabled(false);
	ui.diseaseComboBox->setCurrentIndex(0);
	Q_EMIT diseaseSelectViewFinished(QDialog::Rejected, options_);
}

void DiseaseSelectView::on_diseaseParamSelectViewFinished(int state, const DiseaseSimulation::DiseaseOptions& params)
{
	qDebug() << "DiseaseParamSelectView did finish with state " << state << "\n";
	if (state == QDialog::Accepted)
	{
		options_ = params;
		accept();
	}
}