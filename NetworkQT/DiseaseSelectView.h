#ifndef DISEASESELECTVIEW_H
#define DISEASESELECTVIEW_H

#include "ui_DiseaseSelectView.h"
#include "DiseaseSimulation.h"
#include "DiseaseParamSelectView.h"

class DiseaseSelectView : public QDialog
{
	Q_OBJECT

public:
	DiseaseSelectView(QWidget *parent = 0);
	~DiseaseSelectView();
	void accept();
	void reject();

private:
	Ui::DiseaseSelectView ui;
public Q_SLOTS:
	void on_diseaseComboBox_currentIndexChanged(QString s);
	void on_nextButton_clicked();
	void on_diseaseParamSelectViewFinished(int state, const QMap<DiseaseParamSelectView::Parameters, double>& params);
Q_SIGNALS:
	void diseaseSelectViewFinished(int state, const DiseaseSimulation::DiseaseOptions& options);
private:
	typedef DiseaseSimulation::DiseaseOptions Options;
	Options options_;
	QMap<QString, DiseaseSimulation::ModelType> diseaseTypeMap_;
	DiseaseParamSelectView* paramSelectView_;
};

#endif // DISEASESELECTVIEW_H
