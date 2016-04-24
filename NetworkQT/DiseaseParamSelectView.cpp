#include "stdafx.h"
#include "DiseaseParamSelectView.h"

DiseaseParamSelectView::DiseaseParamSelectView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.infectionPeriodSpinbox->setMinimum(1);
	ui.infectionRateSpinbox->setMinimum(0);
	ui.infectionRateSpinbox->setMaximum(1);
	ui.immunityPeriodSpinbox->setMinimum(1);
	ui.recoveryRateSpinbox->setMinimum(0);
	ui.recoveryRateSpinbox->setMaximum(1);
	ui.immunityLossRateSpinbox->setMinimum(0);
	ui.immunityLossRateSpinbox->setMaximum(1);

	connect(ui.infectionPeriodSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onInfectionPeriodSpinboxValueChanged(const QString&)));
	connect(ui.infectionRateSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onInfectionRateSpinboxValueChanged(const QString&)));
	connect(ui.immunityPeriodSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onImmunityPeriodSpinboxValueChanged(const QString&)));
	connect(ui.immunityLossRateSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onImmunityLossRateSpinbox(const QString&)));
	connect(ui.recoveryRateSpinbox, SIGNAL(valueChanged(const QString&)), this, SLOT(onRecoveryRateSpinbox(const QString&)));

}

DiseaseParamSelectView::~DiseaseParamSelectView()
{
	ui.setupUi(this);
}


void DiseaseParamSelectView::hideImmunity(bool hide)
{
	ui.immunityLossRateButton->setEnabled(!hide);
	ui.immunityLossRateSpinbox->setEnabled(!hide);
	ui.immunityPeriodButton->setEnabled(!hide);
	ui.immunityPeriodSpinbox->setEnabled(!hide);
}

void DiseaseParamSelectView::updateModelType(DiseaseSimulation::ModelType type)
{
	options_.type = type;
	reset();
}

void DiseaseParamSelectView::initialize()
{
	ui.infectionPeriodSpinbox->setValue(ui.infectionPeriodSpinbox->minimum());
	ui.infectionRateSpinbox->setValue(ui.infectionRateSpinbox->minimum());
	ui.immunityPeriodSpinbox->setValue(ui.immunityPeriodSpinbox->minimum());
	ui.immunityLossRateSpinbox->setValue(ui.immunityLossRateSpinbox->minimum());
	ui.recoveryRateSpinbox->setValue(ui.recoveryRateSpinbox->minimum());
	options_.rec_rate_ = ui.recoveryRateSpinbox->value();
	options_.inf_rate_ = ui.infectionRateSpinbox->value();
	options_.imm_period_ = ui.immunityPeriodSpinbox->value();
	options_.imm_loss_rate_ = ui.immunityLossRateSpinbox->value();
	options_.inf_period_ = ui.infectionPeriodSpinbox->value();
}

void DiseaseParamSelectView::reset()
{
	if (options_.type != DiseaseSimulation::ModelType::SIRS)
		hideImmunity(true);
	else
		hideImmunity(false);
	ui.infectionPeriodButton->setChecked(false);
	ui.immunityLossRateButton->setChecked(false);
	ui.immunityPeriodButton->setChecked(false);
	ui.recoveryRateButton->setChecked(false);
	initialize();
}

void DiseaseParamSelectView::accept()
{
	QDialog::accept();
	DiseaseSimulation::DiseaseOptions copy(options_);
	Q_EMIT diseaseParamSelectViewFinished(QDialog::Accepted, copy);
}

void DiseaseParamSelectView::reject()
{
	QDialog::reject();
	DiseaseSimulation::DiseaseOptions copy(options_);
	Q_EMIT diseaseParamSelectViewFinished(QDialog::Rejected, copy);
}

void DiseaseParamSelectView::on_okButton_clicked()
{
	qDebug() << "DiseaseParamSelectView:: ok buttom clicked \n";
	accept();
}


void DiseaseParamSelectView::on_infectionPeriodButton_stateChanged(int s)
{
	if (s == Qt::CheckState::Checked)
	{
		options_.infType_ = DiseaseSimulation::DiseaseOptions::InfectionType::Fixed;
		ui.recoveryRateButton->setChecked(false);
	}
}

void DiseaseParamSelectView::on_recoveryRateButton_stateChanged(int s)
{
	if (s == Qt::CheckState::Checked)
	{
		options_.infType_ = DiseaseSimulation::DiseaseOptions::InfectionType::Probabilistic;
		ui.infectionPeriodButton->setChecked(false);
	}
}

void DiseaseParamSelectView::on_immunityPeriodButton_stateChanged(int s)
{
	if (s == Qt::CheckState::Checked)
	{
		options_.imType_ = DiseaseSimulation::DiseaseOptions::ImmunityType::Fixed;
		ui.immunityLossRateButton->setChecked(false);
	}
}

void DiseaseParamSelectView::on_immunityLossRateButton_stateChanged(int s)
{
	if (s == Qt::CheckState::Checked)
	{
		options_.imType_ = DiseaseSimulation::DiseaseOptions::ImmunityType::Probabilistic;
		ui.immunityPeriodButton->setChecked(false);
	}
}

void DiseaseParamSelectView::onImmunityLossRateSpinbox(const QString& text)
{
	options_.imm_loss_rate_ = ui.immunityLossRateSpinbox->value();
}

void DiseaseParamSelectView::onRecoveryRateSpinbox(const QString& text)
{
	options_.rec_rate_ = ui.recoveryRateSpinbox->value();
}

void DiseaseParamSelectView::onInfectionRateSpinboxValueChanged(const QString& text)
{
	options_.inf_rate_ = ui.infectionRateSpinbox->value();
}

void DiseaseParamSelectView::onInfectionPeriodSpinboxValueChanged(const QString& text)
{
	options_.inf_period_ = ui.infectionPeriodSpinbox->value();
}

void DiseaseParamSelectView::onImmunityPeriodSpinboxValueChanged(const QString& text)
{
	options_.imm_period_ = ui.immunityPeriodSpinbox->value();
}