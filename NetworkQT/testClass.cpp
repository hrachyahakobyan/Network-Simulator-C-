#include "stdafx.h"
#include "testClass.h"

testClass::testClass(QWidget *parent)
	: QObject(parent)
{

}

testClass::~testClass()
{

}

void testClass::receive_message()
{
	QTextStream out(stdout);
	out << "console application\n";
}