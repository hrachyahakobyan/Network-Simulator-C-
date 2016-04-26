#include "stdafx.h"
#include "networkqt.h"
#include "BroadcastSimulation.h"
#include "RandomTest.h"
#include <QtWidgets/QApplication>

#define QtAPP false


int main(int argc, char *argv[])
{
	if (QtAPP == true)
	{
		QApplication a(argc, argv);
		NetworkQT* w = new NetworkQT();
		w->show();
		return a.exec();
	}
	else
	{
		GraphBuilder::GraphOptions g;
		g.type_ = GraphBuilder::GraphOptions::GraphType::Graph_Random;
		g.n_vertices_ = 100;
		g.p_ = 20;
		BroadcastSchemeOptions op;
		op.send_type_ = SEND_SCHEME_M2;
		op.receive_type_ = RECEIVE_SCHEME_M;
		op.finish_type_ = FINISH_SCHEME_M;
		TestOptions top;
		top.iterCount_ = 30;
		RandomTest t;
		t.test(g, op, top);
		CleanUp::cleanUp();
		return 0;
	}
}
