// QTProject.cpp : Defines the entry point for the application.
//

#ifndef MAIN_H
#define MAIN_H

#include "main.h"

using namespace std;


int main(int argc, char** argv)
{	
	// QT-Game-UI
#define USE_UI true;
#if USE_UI
	QApplication app(argc, argv);

	// Chess-stuff
	
	QGraphicsScene scene;
	Chessboard chessboard(app, &scene, QSize(960, 540));

	//app.setActiveWindow(&chessboard);

	chessboard.display();

	app.exec();

#else 
	_setmode(_fileno(stdout), _O_U16TEXT);
	chessboard.print();
	system("pause");

#endif
}

#endif 