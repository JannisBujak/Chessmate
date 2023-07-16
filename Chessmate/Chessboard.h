#pragma once 

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <vector>

#include <QDebug>
#include <QFile>

#include "ChessboardField.h"
#include "Pieces.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

/*Drawing the playing-field here*/
class Chessboard : public QGraphicsView
{
	Q_OBJECT
private:
	QApplication& m_application;

	std::vector<std::unique_ptr<ChessboardField>> m_rect_items;
	std::vector<std::shared_ptr<Piece>> white, black;
	
	const wchar_t w = L'\u2659'
		, b = L'\u265F';

	const QChar qw = QChar(0x59, 0x26);

	const QString m_filename = QString("../../../../Chessmate/chess-icon/vecteezy_chess_icon-removebg.png");
	// const QString m_filename = QString(":/QTProject/chess-icon/vecteezy_chess_icon.jpg");
		
public:
	static std::vector<QPixmap> create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp);

public:
	Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect);
	
	template <typename T>
	void addPiece(Color a_color, int a_col, int a_row);
	
	void fillBackrow(Color a_color, int a_col);
	void init();

	ChessboardField* fieldAt(int x, int y);
	ChessboardField* fieldAtScenePos(QPointF a_scPos);
	ChessboardField* display_field(int x, int y, const QRectF& a_rect);
	void display_label(int x, int y, const QRectF& a_rect, const QPixmap& a_pxmp);
	void display();
	void print();

	void resizeEvent(QResizeEvent* event) override;
};

template<typename T>
inline void Chessboard::addPiece(Color a_color, int a_col, int a_row)
{
	std::shared_ptr<T> piece = std::make_shared<T>(a_col, a_row, a_color);
	((a_color == Color::White) ? white : black).push_back(piece);	
	this->fieldAt(a_col, a_row)->setPiece(piece);
}
