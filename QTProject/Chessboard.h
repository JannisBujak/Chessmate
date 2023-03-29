
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
#include <QFile>


/*Drawing the playing-field here*/
class Chessboard : public QGraphicsView
{
private:
	QApplication& m_application;
	ChessGame m_chessgame;
	std::vector<std::unique_ptr<QGraphicsRectItem>> m_rect_items;
	std::vector<std::unique_ptr<QLabel>> m_labels;
	std::vector<std::unique_ptr<QImage>> m_images;
	
	const wchar_t w = L'\u2659'
		, b = L'\u265F';

	const QChar qw = QChar(0x59, 0x26);

	const QString m_filename = QString("../../../../QTProject/chess-icon/vecteezy_chess_icon.jpg");
	// const QString m_filename = QString(":/QTProject/chess-icon/vecteezy_chess_icon.jpg");
	
	
	std::vector<QPixmap> m_pxmaps;


public:
	static std::vector<QPixmap> create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp);

public:
	Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect);
	

	void display_rect(int x, int y, const QRectF& a_rect);
	void display_label(int x, int y, const QRectF& a_rect, QPixmap& a_pxmp);
	void display();
	void print();

	void resizeEvent(QResizeEvent* event) override;
};


#endif