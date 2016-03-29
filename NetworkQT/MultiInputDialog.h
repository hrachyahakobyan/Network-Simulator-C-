#ifndef MULTIINPUTDIALOG_H
#define MULTIINPUTDIALOG_H

#include <QDialog>

class MultiInputDialog : public QDialog
{
	Q_OBJECT

public:
	MultiInputDialog(QWidget *parent);
	MultiInputDialog(QWidget *parent, QList<QString> labels, QString title_ = "Input form");
	virtual ~MultiInputDialog();
	virtual void addInputs(QList<QString> labels);
protected:
	QList<QString> labels_;
	QList<QLineEdit*> lines_;
	QDialogButtonBox* buttons_;
	QPushButton* ok_button_;
	QPushButton* cancel_button_;
	QFormLayout* form_;
	QMap<int, QString> lines_map_;
	QMap<QString, QString> inputs_map_;
public Q_SLOTS:
	 virtual void  lineTextChanged(const QString& s);
	 virtual void okButtonClicked();
	 virtual void cancelButtonClicked();
protected:
	 virtual bool validate();
};

#endif // MULTIINPUTDIALOG_H
