#ifndef DISEASEPARAMSELECTVIEW_H
#define DISEASEPARAMSELECTVIEW_H

#include "ui_DiseaseParamSelectView.h"

class DiseaseParamSelectView : public QDialog
{
	Q_OBJECT

public:
	enum Parameters{InfectionRate, InfectionPeriod, ImmunityPeriod};
public:
	DiseaseParamSelectView(QWidget *parent = 0);
	~DiseaseParamSelectView();
	void accept();
	void reject();
	void updateParams(const QMap<Parameters, bool>& paramsMap);
public Q_SLOTS:
	void onInfectionRateSpinboxValueChanged(const QString& text);
	void onInfectionPeriodSpinboxValueChanged(const QString& text);
	void onImmunityPeriodSpinboxValueChanged(const QString& text);
	void on_okButton_clicked();
private:
	Ui::DiseaseParamSelectView ui;
	QMap<Parameters, double> options_;
private:
	void reset();
	void initialize();
Q_SIGNALS:
	void diseaseParamSelectViewFinished(int state, const QMap<DiseaseParamSelectView::Parameters, double>& options);
};

#endif // DISEASEPARAMSELECTVIEW_H
