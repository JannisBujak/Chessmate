#include "ChessboardField.h"

#include "Chessboard.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

ChessboardField::ChessboardField(char a_column, char a_row, Chessboard* a_parentCB)
	: m_parentCB(a_parentCB)
	, m_column(a_column)
	, m_row(a_row)
	, m_pxmapItem(nullptr)
{
	qDebug() << "Created field" << getText();
	static int ct = 0;

	setAcceptDrops(true); 
}

QString ChessboardField::getText()
{
	return QString().asprintf("%c%d", m_column, m_row);
}

void ChessboardField::setPixmap(QPixmap a_pxmp)
{
	m_pixmap = std::make_unique<QPixmap>(a_pxmp);
	/*
	m_pxmapItem = new QGraphicsPixmapItem(this);
	m_pxmapItem->clearFocus();
	m_pxmapItem->setPixmap(a_pxmp);
	*/
}

void ChessboardField::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (!m_draggedPiece && m_pixmap)
	{
		QRectF bounding = sceneBoundingRect();
		
		m_pxmapItem = std::make_unique<QGraphicsPixmapItem>(this);
		m_pxmapItem->setPixmap(m_pixmap->scaled(bounding.size().toSize()));
		m_pxmapItem->setPos(bounding.topLeft());
	}
	QGraphicsRectItem::paint(painter, option, widget);
}

void ChessboardField::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(m_draggedPiece)
		m_draggedPiece->setPos(event->scenePos());
}

void ChessboardField::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Click" << getText();
	if (m_pixmap)
	{
		// Set m_draggedPiece
		m_pxmapItem.reset();
		m_draggedPiece = std::make_unique<QGraphicsPixmapItem>(this);
		m_draggedPiece->setPixmap(m_pixmap->scaled(boundingRect().size().toSize()));
		m_draggedPiece->setZValue(1);
		m_draggedPiece->setPos(event->pos());

	}
}

void ChessboardField::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	m_draggedPiece.reset();
}

