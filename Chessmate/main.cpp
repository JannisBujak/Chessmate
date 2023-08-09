// QTProject.cpp : Defines the entry point for the application.
//

#include "main.h"

#include "qgraphicslinearlayout.h"

#define USE_UI true

using namespace std;


int main(int argc, char** argv)
{	
	// QT-Game-UI

#if USE_UI
	QApplication app(argc, argv);

	// Chess-stuff
	
	QGraphicsScene scene;
	QGraphicsView view;	

	QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
	QVBoxLayout layout;
	
	Chessboard* chessgame = new Chessboard(app, &scene, QSize(960, 540));

	windowLayout->addItem(chessgame);

	view.setLayout(windowLayout);
	view.display();
	
	// chessgame->display();
	
	QVBoxLayout layout;
	app.exec();

#else 
	_setmode(_fileno(stdout), _O_U16TEXT);
	chessboard.print();
	system("pause");

#endif
}
