// QTProject.cpp : Defines the entry point for the application.
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
	Chessgame chessgame(app, &scene, QSize(960, 540));

	chessgame.display();
	
	QVBoxLayout layout;
	app.exec();

#else 
	_setmode(_fileno(stdout), _O_U16TEXT);
	chessboard.print();
	system("pause");

#endif
}
