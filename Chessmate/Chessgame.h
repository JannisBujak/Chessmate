#pragma once 

#include <iostream>
#include <qgraphicsscene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <vector>
#include <QGraphicsLayoutItem>

#include <QBoxLayout>

#include <QDebug>
#include <QFile>

#include "ChessboardField.h"
#include "Pieces.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

/*Drawing the playing-field here*/
class Chessgame : public QGraphicsView, public QGraphicsLayoutItem
{
	Q_OBJECT
private:
	Color m_playingColor;

	std::shared_ptr<QGraphicsTextItem> m_infoButton;
	std::vector<std::shared_ptr<ChessboardField>> m_fields;
	std::vector<std::shared_ptr<Pieces::Piece>> white, black;
	
	const wchar_t w = L'\u2659'
		, b = L'\u265F';

	const QChar qw = QChar(0x59, 0x26);

	const QString m_filename = QString("../../../../Chessmate/chess-icon/vecteezy_chess_icon-removebg.png");
	// const QString m_filename = QString(":/QTProject/chess-icon/vecteezy_chess_icon.jpg");
		
public:
	static std::vector<QPixmap> create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp);

public:
	Chessgame(QGraphicsScene* a_scene);
	
	Color playingColor();

	void togglePlayingColor();

	void setPlayingColor(Color a_playingColor);

	template <typename T>
	void addPiece(Color a_color, int a_col, int a_row);
	
	void fillBackrow(Color a_color, int a_col);

	void removeAllPieces();

public slots:
	void init();

public:
	std::shared_ptr<Pieces::Piece> pieceAt(int x, int y) const;

	ChessboardField* fieldAt(int x, int y);

	ChessboardField* fieldAtScenePos(QPointF a_scPos);
	ChessboardField* display_field(int x, int y, const QRectF& a_rect);
	void display_label(int x, int y, const QRectF& a_rect, const QPixmap& a_pxmp);
	void display();
	void print();

	void markLegalMoves(std::shared_ptr<Pieces::Piece> a_piece);
	void markNoMoves();

	bool isMoveable(std::shared_ptr<Pieces::Piece> a_piece);
	
	static Pieces::King* getKingFromList(std::vector < std::shared_ptr<Pieces::Piece>> a_ColoredPieces);
	Pieces::King* getKingFromList(Color a_color);
	
	std::vector<std::shared_ptr<Pieces::Piece>> getListOfColor(Color a_color);

	void checkForWin();
	void confirmMove();

	template <typename T>
	static void deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list);

	void cleanPiece(std::shared_ptr<Pieces::Piece> a_piece);

	void resizeEvent(QResizeEvent* event) override;

	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

signals:
	void playingColorChanged(Color);
	void playerWon(Color);

public:
	bool handlePieceDraggedFromTo(ChessboardField* drag_from, ChessboardField* drag_to);
};

template<typename T>
inline void Chessgame::addPiece(Color a_color, int a_col, int a_row)
{
	std::shared_ptr<T> piece = std::make_shared<T>(a_col, a_row, a_color);
	((a_color == Color::White) ? white : black).push_back(piece);	
	this->fieldAt(a_col, a_row)->setPiece(piece);
}

template<typename T>
inline void Chessgame::deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (it->get() == element.get())
		{
			list.erase(it);
			break;
		}
	}
}
