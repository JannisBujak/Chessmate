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

    auto playingPartyText = new QLabel();
    main_layout->addWidget(playingPartyText);
    auto inner_scene = new QGraphicsScene();
    
    auto chessgame = new Chessgame(inner_scene);
    main_layout->addWidget(chessgame);
    
    app->connect(chessgame, &Chessgame::playingColorChanged, [&](Color a_color)
        {
            playingPartyText->setText(QString("%1 team playing").arg(a_color == Color::White ? QString("White") : QString("Black")));
        });

    auto restartGameButton = new QPushButton();
    main_layout->addWidget(restartGameButton);

    app->connect(restartGameButton, &QPushButton::clicked, chessgame, &Chessgame::init);

    chessgame->init();

    // outer_view->setBaseSize(QSize(960, 540));
    outer_view->resize(QSize(1920, 1080));
    outer_view->show();
    app->exec();
}
