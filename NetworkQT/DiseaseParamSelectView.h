#ifndef DISEASEPARAMSELECTVIEW_H
#define DISEASEPARAMSELECTVIEW_H

#include "ui_DiseaseParamSelectView.h"
#include "DiseaseSimulation.h"

class DiseaseParamSelectView : public QDialog
{
	Q_OBJECT

public:
	DiseaseParamSelectView(QWidget *parent = 0);
	~DiseaseParamSelectView();
	void accept();
	void reject();
	void updateModelType(DiseaseSimulation::ModelType type);
public Q_SLOTS:
	void onInfectionRateSpinboxValueChanged(const QString& text);
	void onInfectionPeriodSpinboxValueChanged(const QString& text);
	void onImmunityPeriodSpinboxValueChanged(const QString& text);
	void onImmunityLossRateSpinbox(const QString& text);
	void onRecoveryRateSpinbox(const QString& text);
	void on_infectionPeriodButton_stateChanged(int s);
	void on_recoveryRateButton_stateChanged(int s);
	void on_immunityPeriodButton_stateChanged(int s);
	void on_immunityLossRateButton_stateChanged(int s);
	void on_okButton_clicked();
private:
	Ui::DiseaseParamSelectView ui;
	DiseaseSimulation::DiseaseOptions options_;
private:
	void reset();
	void initialize();
	void hideImmunity(bool hide);
Q_SIGNALS:
	void diseaseParamSelectViewFinished(int state, const DiseaseSimulation::DiseaseOptions& options);
};

#endif // DISEASEPARAMSELECTVIEW_H
