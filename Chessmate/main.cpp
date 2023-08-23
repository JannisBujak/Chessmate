// QTProject.cpp : Defines the entry point for the application.
//

#include "main.h"

#include "qgraphicslinearlayout.h"

using namespace std;

int main(int argc, char** argv)
{	
	// QT-Game-UI
	QApplication app(argc, argv);

	// Chess-stuff

	auto outer_scene = new QGraphicsScene(&app);
    auto outer_view = new QGraphicsView (outer_scene);

    auto main_layout = new QVBoxLayout();
    outer_view->setLayout(main_layout);

    main_layout->addWidget(new QLabel("Text"));
    QGraphicsScene inner_scene;
    Chessboard* chessgame = new Chessboard(app, &inner_scene, QSize(960, 540));
    chessgame->display();

    main_layout->addWidget(chessgame);

    outer_view->show();
    app.exec();
}
