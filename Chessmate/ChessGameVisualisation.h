#pragma once 

#include <iostream>
#include <QGraphicsScene>
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

class ChessGame : public QObject
{
	Q_OBJECT
private:
	Color m_playingColor;
	std::vector<std::shared_ptr<Pieces::Piece>> white, black;

public:
	ChessGame(QObject* parent = nullptr);
	ChessGame(const ChessGame&);

	template <typename T>
	void addPiece(Color a_color, int a_col, int a_row);


	template <typename T>
	static void deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list);

	Color playingColor();
	void togglePlayingColor();
	void setPlayingColor(Color a_playingColor);

	void fillBackrow(Color a_color, int a_col);
	void removeAllPieces();
	std::shared_ptr<Pieces::Piece> pieceAt(int x, int y) const;
		
	bool isMoveable(std::shared_ptr<Pieces::Piece> a_piece);
	
	static Pieces::King* getKingFromList(std::vector < std::shared_ptr<Pieces::Piece>> a_ColoredPieces);
	Pieces::King* getKingFromList(Color a_color);
	
	const std::vector<std::shared_ptr<Pieces::Piece>> getListOfColor(Color a_color) const;
	std::vector<std::shared_ptr<Pieces::Piece>> getListOfColor(Color a_color);
	std::vector<std::shared_ptr<Pieces::Piece>> getListOfPieces();

	void checkForWin();
	void confirmMove();

	void cleanPiece(std::shared_ptr<Pieces::Piece> a_piece);

public slots:
	void init();
signals:
	void playingColorChanged(Color);
	void playerWon(Color);
};

/*Drawing the playing-field here*/
class ChessGameVisualisation : public QGraphicsView
{
	Q_OBJECT
private:
	std::shared_ptr<QGraphicsTextItem> m_infoButton;
	std::vector<std::shared_ptr<ChessboardField>> m_fields;
	
	const QString m_filename = QString("../../../../Chessmate/chess-icon/vecteezy_chess_icon-removebg.png");

    ChessGame m_ChessGame;

public:
	static std::vector<QPixmap> create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp);

public:
	ChessGameVisualisation(QGraphicsScene* a_scene);

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
    const ChessGame* getChessGame();
	
	void resizeEvent(QResizeEvent* event) override;

public:
	bool handlePieceDraggedFromTo(ChessboardField* drag_from, ChessboardField* drag_to);

    void cleanPiece(std::shared_ptr<Pieces::Piece> sharedPtr);

    bool isMoveable(std::shared_ptr<Pieces::Piece> sharedPtr);
};

template<typename T>
inline void ChessGame::addPiece(Color a_color, int a_col, int a_row)
{
	std::shared_ptr<T> piece = std::make_shared<T>(a_col, a_row, a_color);
	((a_color == Color::White) ? white : black).push_back(piece);
}

template<typename T>
inline void ChessGame::deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list)
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
