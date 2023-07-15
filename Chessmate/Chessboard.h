#pragma once 

#include "ChessGame.h"
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>

#include <QDebug>
#include <QFile>

#include "ChessboardField.h"

/*Drawing the playing-field here*/
class Chessboard : public QGraphicsView
{
	Q_OBJECT
private:
	QApplication& m_application;
	ChessGame m_chessgame;

	std::vector<std::unique_ptr<ChessboardField>> m_rect_items;
	
	const wchar_t w = L'\u2659'
		, b = L'\u265F';

	const QChar qw = QChar(0x59, 0x26);

	const QString m_filename = QString("../../../../Chessmate/chess-icon/vecteezy_chess_icon-removebg.png");
	// const QString m_filename = QString(":/QTProject/chess-icon/vecteezy_chess_icon.jpg");
		
public:
	static std::vector<QPixmap> create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp);

public:
	Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect);
	
	ChessboardField* getFieldAt(int x, int y);
	ChessboardField* getFieldAtScenePos(QPointF a_scPos);
	ChessboardField* display_field(int x, int y, const QRectF& a_rect);
	void display_label(int x, int y, const QRectF& a_rect, QPixmap& a_pxmp);
	void display();
	void print();

	ChessGame& Game();

	void resizeEvent(QResizeEvent* event) override;
};

