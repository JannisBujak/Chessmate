// QTProject.cpp : Defines the entry point for the application.
//

#ifndef MAIN_H
#define MAIN_H

#include "main.h"

using namespace std;


int main(int argc, char** argv)
{	
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Chess-stuff
	ChessGame game;
	Chessboard board;
	board.print(game);


	// QT-Game-UI
#define USE_UI true;
#if USE_UI

	QApplication app(argc, argv);

	QGraphicsScene* gScene = new QGraphicsScene();
	
	
	QGraphicsView* view = new QGraphicsView(gScene);
	auto gv_size = view->size();

	QGraphicsRectItem* rect = new QGraphicsRectItem();
	rect->setRect(QRectF(0, 0, gv_size.width(), gv_size.height()));
	gScene->addItem(rect);

	
	view->show();
	app.exec();

#else 
	system("pause");
#endif
}

#endif 