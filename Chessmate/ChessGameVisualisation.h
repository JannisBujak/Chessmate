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

#include "ChessGame.h"
#include "ChessboardField.h"
#include "Pieces.h"

#define MARK_MOVES true

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
	ChessboardField* fieldAt(int x, int y);
	ChessboardField* fieldAt(QPoint point);

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
