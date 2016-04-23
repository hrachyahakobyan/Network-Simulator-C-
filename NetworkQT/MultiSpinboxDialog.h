#ifndef MULTISPINBOXDIALOG_H
#define MULTISPINBOXDIALOG_H


class MultiSpinboxDialog : public QDialog
{
	Q_OBJECT

public:
	MultiSpinboxDialog(QWidget *parent);
	MultiSpinboxDialog(QWidget *parent, QList<QPair<QString, QPair<int, int>>> spinBoxes, QString title = "Input");
	virtual ~MultiSpinboxDialog();

	void accept();
	void reject();

protected:
	QList<QPair<QString, QSpinBox*>> spinBoxes_;
	QDialogButtonBox* buttons_;
	QPushButton* ok_button_;
	QPushButton* cancel_button_;
	QFormLayout* form_;
	QMap<QString, int> inputs_map_;
protected:
	virtual bool validate();
	virtual void updateValues();
public Q_SLOTS:
	virtual void spinBoxChanged(const QString& text);
	virtual void okButtonClicked();
	virtual void cancelButtonClicked();
Q_SIGNALS:
	void multiSpinboxDialogDidFinish(int state, const QMap<QString, int>& result);
};

#endif // MULTISPINBOXDIALOG_H
