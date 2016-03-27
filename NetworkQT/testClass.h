#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class testClass : public QObject
{
	Q_OBJECT

public:
	testClass(QWidget *parent);
	~testClass();

private:

public Q_SLOTS :
	void receive_message();
	
};

#endif // TESTCLASS_H
