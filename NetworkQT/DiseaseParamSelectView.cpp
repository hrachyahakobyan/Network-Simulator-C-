#include "stdafx.h"
#include "DiseaseParamSelectView.h"

DiseaseParamSelectView::DiseaseParamSelectView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.infectionPeriodSpinbox->setMinimum(1);
	ui.infectionRateSpinbox->setMinimum(0);
	ui.infectionRateSpinbox->setMaximum(1);
	ui.immunityPeriodSpinbox->setMinimum(0);

	connect(ui.infectionPeriodSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onInfectionPeriodSpinboxValueChanged(const QString&)));
	connect(ui.infectionRateSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onInfectionRateSpinboxValueChanged(const QString&)));
	connect(ui.immunityPeriodSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onImmunityPeriodSpinboxValueChanged(const QString&)));
}

DiseaseParamSelectView::~DiseaseParamSelectView()
{
	ui.setupUi(this);
}

void DiseaseParamSelectView::updateParams(const QMap<Parameters, bool>& paramsMap)
{
	ui.infectionPeriodSpinbox->setEnabled(paramsMap[Parameters::InfectionPeriod]);
	ui.infectionRateSpinbox->setEnabled(paramsMap[Parameters::InfectionRate]);
	ui.immunityPeriodSpinbox->setEnabled(paramsMap[Parameters::ImmunityPeriod]);
	initialize();
}

void DiseaseParamSelectView::initialize()
{
	ui.infectionPeriodSpinbox->setValue(ui.infectionPeriodSpinbox->minimum());
	ui.infectionRateSpinbox->setValue(ui.infectionRateSpinbox->minimum());
	ui.immunityPeriodSpinbox->setValue(ui.immunityPeriodSpinbox->minimum());
}

void DiseaseParamSelectView::reset()
{
	ui.infectionPeriodSpinbox->setEnabled(false);
	ui.infectionRateSpinbox->setEnabled(false);
	ui.immunityPeriodSpinbox->setEnabled(false);
	options_.clear();
	initialize();
}

void DiseaseParamSelectView::accept()
{
	QDialog::accept();
	Q_EMIT diseaseParamSelectViewFinished(QDialog::Accepted, options_);
	reset();
}

void DiseaseParamSelectView::reject()
{
	QDialog::reject();
	Q_EMIT diseaseParamSelectViewFinished(QDialog::Rejected, options_);
	reset();
}

void DiseaseParamSelectView::on_okButton_clicked()
{
	qDebug() << "DiseaseParamSelectView:: ok buttom clicked \n";
	accept();
}

void DiseaseParamSelectView::onInfectionRateSpinboxValueChanged(const QString& text)
{
	options_[Parameters::InfectionRate] = ui.infectionRateSpinbox->value();
}

void DiseaseParamSelectView::onInfectionPeriodSpinboxValueChanged(const QString& text)
{
	options_[Parameters::InfectionPeriod] = ui.infectionPeriodSpinbox->value();
}

void DiseaseParamSelectView::onImmunityPeriodSpinboxValueChanged(const QString& text)
{
	options_[Parameters::ImmunityPeriod] = ui.immunityPeriodSpinbox->value();
}