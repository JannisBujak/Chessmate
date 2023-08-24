#pragma once 

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>

#include "Pieces.h"

class Chessgame;

class ChessboardField : public QGraphicsRectItem
{
private:
	Chessgame* m_chessgame;	
	char m_column, m_row;
	
	std::shared_ptr<Pieces::Piece> m_piece;
	std::unique_ptr<QGraphicsPixmapItem> m_pxmapItem;

	std::unique_ptr<QGraphicsEllipseItem> m_legalMarker;
	std::unique_ptr<QGraphicsPixmapItem> m_draggedPiece;

public:
	ChessboardField(char x, char y, Chessgame* a_chessgame);
	QString getText();

	void updateDraggedPos(QGraphicsSceneMouseEvent* event);
	QPoint getBoardPos() const;

	void setPiece(std::shared_ptr<Pieces::Piece> a_piece = std::shared_ptr<Pieces::Piece>());
	std::shared_ptr<Pieces::Piece> getPiece();

	void setMarkLegal(bool a_marked);
	void cleanPiece();
protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* even) override;
};
