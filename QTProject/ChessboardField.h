#pragma once 

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>


class Chessboard;

class ChessboardField : public QGraphicsRectItem
{
private:
	QGraphicsScene* m_scene;	
	std::unique_ptr<QPixmap> m_pixmap;
	
	char m_column, m_row;
	std::unique_ptr<QGraphicsPixmapItem> m_pxmapItem;

	std::unique_ptr<QGraphicsPixmapItem> m_draggedPiece;

public:
	ChessboardField(char x, char y, QGraphicsScene* a_scene);
	QString getText();

	void setPixmap(QPixmap a_pxmp);

	void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option, QWidget* widget);
	void updateDraggedPos(QGraphicsSceneMouseEvent* event);
protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* even) override;
};
