#pragma once 

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>


class Chessboard;

class ChessboardField : public QGraphicsRectItem
{
private:
	Chessboard* m_parentCB;	
	std::unique_ptr<QPixmap> m_pixmap;
	std::unique_ptr<QGraphicsPixmapItem> m_pxmapItem;
	char m_column, m_row;

	std::unique_ptr<QGraphicsPixmapItem> m_draggedPiece;

public:
	ChessboardField(char x, char y, Chessboard* a_parentCB = nullptr);
	QString getText();

	void setPixmap(QPixmap a_pxmp);

	void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option, QWidget* widget);


protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* even) override;
};
