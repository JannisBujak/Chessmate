// QTProject.cpp : Defines the entry point for the application.
//

#include "QTProject.h"


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
	std::wcout << '\u2659' << std::endl;

#if 0 
	ChessGame game;
	Chessboard board;
	board.print(game);
#endif 
	system("pause");
}
