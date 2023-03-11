// QTProject.cpp : Defines the entry point for the application.
//

#include "QTProject.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>
#include <qsizepolicy.h>

using namespace std;

#include <io.h>
#include <fcntl.h>

int main(int argc, char** argv)
{	
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*
	QApplication app(argc, argv);

	QPushButton button;
	button.setText("My text");
	button.setToolTip("A tooltip");
	button.show();

	return app.exec();
	*/
	
#if 1
	ChessGame game;
	Chessboard board;
	board.print(game);

	QApplication app(argc, argv);
	QWidget window;
	window.resize(320, 240);
	window.show();
	window.setWindowTitle(
		QApplication::translate("toplevel", "Top-level widget"));
	
	QVBoxLayout vLayout;
	
	QGridLayout gridLayout;
	
	gridLayout.setSpacing(0);

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			QPushButton* pbtn = new QPushButton();
			
			pbtn->setSizePolicy(QSizePolicy::Expanding);
			// gridLayout.addWidget(new QFrame(), y, x);
			gridLayout.addWidget(pbtn, y, x);
		}
	}
		
	vLayout.addLayout(&gridLayout);
	vLayout.addWidget(new QPushButton("Ok"));
	window.setLayout(&vLayout);

	return app.exec();

#endif 
	system("pause");
}
