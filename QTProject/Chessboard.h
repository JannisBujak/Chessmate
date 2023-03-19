
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessGame.h"
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>

#include <QDebug>


/*Drawing the playing-field here*/
class Chessboard : public QGraphicsView
{
private:
	QApplication& m_application;
	ChessGame m_chessgame;
	std::vector<std::unique_ptr<QGraphicsRectItem>> m_rect_items;
	std::vector<std::unique_ptr<QLabel>> m_labels;
public:
	Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect);
	void display();
	void print();

	void resizeEvent(QResizeEvent* event) override;
};


#endif