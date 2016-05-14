#include "stdafx.h"
#include "networkqt.h"
#include "BroadcastSimulation.h"
#include "BroadcastTest.h"
#include <QtWidgets/QApplication>

#define QtAPP true


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
		g.type_ = GraphBuilder::GraphOptions::GraphType::Graph_Complete;
		g.n_vertices_ = 100;
		BroadcastSchemeOptions op;
		op.send_type_ = SEND_SCHEME_M1;
		op.receive_type_ = RECEIVE_SCHEME_M;
		op.finish_type_ = FINISH_SCHEME_M;
		TestOptions top;
		top.iterCount_ = 100;
		BroadcastTest t;
		t.test(g, op, top);
		CleanUp::cleanUp();
		return 0;
	}
}
