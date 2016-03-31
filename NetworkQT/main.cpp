#include "stdafx.h"
#include "networkqt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NetworkQT* w = new NetworkQT();
	w->show();
	return a.exec();












	/*
	#include <QTextStream>
	QTextStream out(stdout);
	out << "console application\n";
	*/
}
