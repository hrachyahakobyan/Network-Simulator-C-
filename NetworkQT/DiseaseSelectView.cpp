#include "stdafx.h"
#include "DiseaseSelectView.h"

DiseaseSelectView::DiseaseSelectView(QWidget *parent)
	: QDialog(parent), paramSelectView_(0)
{
	ui.setupUi(this);
	ui.nextButton->setEnabled(false);
	paramSelectView_ = new DiseaseParamSelectView(this);
	connect(paramSelectView_, SIGNAL(diseaseParamSelectViewFinished(int, const QMap<DiseaseParamSelectView::Parameters, double>&)), this, SLOT(on_diseaseParamSelectViewFinished(int, const QMap<DiseaseParamSelectView::Parameters, double>&)));
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
	typedef DiseaseParamSelectView::Parameters P;
	typedef DiseaseSimulation::ModelType M;
	QMap<P, bool> params;
	switch (options_.type)
	{
	case M::SIR:
		params[P::ImmunityPeriod] = false;
		params[P::InfectionPeriod] = true;
		params[P::InfectionRate] = true;
		break;
	case M::SIS:
		params[P::ImmunityPeriod] = false;
		params[P::InfectionPeriod] = true;
		params[P::InfectionRate] = true;
		break;
	case M::SIRS:
		params[P::ImmunityPeriod] = true;
		params[P::InfectionPeriod] = true;
		params[P::InfectionRate] = true;
		break;
	}
	paramSelectView_->updateParams(params);
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

void DiseaseSelectView::on_diseaseParamSelectViewFinished(int state, const QMap<DiseaseParamSelectView::Parameters, double>& params)
{
	qDebug() << "DiseaseParamSelectView did finish with state " << state << "\n";
	if (state == QDialog::Accepted)
	{
		options_.inf_period_ = params[DiseaseParamSelectView::Parameters::InfectionPeriod];
		options_.inf_rate_ = params[DiseaseParamSelectView::Parameters::InfectionRate];
		options_.imm_period_ = params[DiseaseParamSelectView::Parameters::ImmunityPeriod];
		accept();
	}
}