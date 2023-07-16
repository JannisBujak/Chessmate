﻿// QTProject.cpp : Defines the entry point for the application.
//

#include "main.h"
#define USE_UI true

using namespace std;


int main(int argc, char** argv)
{	
	// QT-Game-UI

#if USE_UI
	QApplication app(argc, argv);

	// Chess-stuff
	
	QGraphicsScene scene;
	Chessboard chessgame(app, &scene, QSize(960, 540));

	//app.setActiveWindow(&chessboard);

	chessgame.display();
	
	app.exec();

#else 
	_setmode(_fileno(stdout), _O_U16TEXT);
	chessboard.print();
	system("pause");

#endif
}
