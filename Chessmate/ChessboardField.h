#pragma once 

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>

#include "Pieces.h"

class Chessboard;

class ChessboardField : public QGraphicsRectItem
{
private:
	Chessboard* m_chessboard;	
	char m_column, m_row;
	
	std::shared_ptr<Piece> m_piece;
	std::unique_ptr<QGraphicsPixmapItem> m_pxmapItem;


	std::unique_ptr<QGraphicsPixmapItem> m_draggedPiece;

public:
	ChessboardField(char x, char y, Chessboard* a_chessboard);
	QString getText();


	void updateDraggedPos(QGraphicsSceneMouseEvent* event);
	QPointF getBoardPos() const;

	void setPiece(std::shared_ptr<Piece> a_piece = std::shared_ptr<Piece>());
	std::shared_ptr<Piece> getPiece();

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* even) override;
};
