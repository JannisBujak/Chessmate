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

	QGraphicsLinearLayout* windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
	
	// Chessgame chessgame(app, &scene, QSize(960, 540));
	
	QGraphicsLinearLayout* innerLayout = new QGraphicsLinearLayout(Qt::Vertical, windowLayout);
	QGraphicsSimpleTextItem text("Henlo");

	windowLayout->addItem(innerLayout);
	//windowLayout->addItem(&chessgame);

	// scene.addWidget(widget);
	// view.setLayout(windowLayout);
	
	// chessgame.display();
	
	app.exec();

#else 
	_setmode(_fileno(stdout), _O_U16TEXT);
	chessboard.print();
	system("pause");

#endif
}
