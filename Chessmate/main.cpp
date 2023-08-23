// QTProject.cpp : Defines the entry point for the application.
//

#include "main.h"

#include "qgraphicslinearlayout.h"

using namespace std;

int main(int argc, char** argv)
{	
	// QT-Game-UI
	auto app = new QApplication(argc, argv);

	// Chess-stuff

	auto outer_scene = new QGraphicsScene(app);
    auto outer_view = new QGraphicsView (outer_scene);

    auto main_layout = new QVBoxLayout();
    outer_view->setLayout(main_layout);

    main_layout->addWidget(new QLabel("Text"));
    auto inner_scene = new QGraphicsScene();
    auto chessgame = new Chessgame(inner_scene);
    chessgame->display();

    main_layout->addWidget(chessgame);

    // outer_view->setBaseSize(QSize(960, 540));
    outer_view->resize(QSize(1920, 1080));
    outer_view->show();
    app->exec();
}
