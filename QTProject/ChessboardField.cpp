#include "ChessboardField.h"

#include "Chessboard.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

ChessboardField::ChessboardField(char a_column, char a_row, QGraphicsScene* a_scene)
	: m_scene(a_scene)
	, m_column(a_column)
	, m_row(a_row)
	, m_pxmapItem(nullptr)
{
	qDebug() << "Created field" << getText();
	
	setAcceptDrops(true); 
}

QString ChessboardField::getText()
{
	return QString().asprintf("%c%d", m_column, m_row);
}

void ChessboardField::setPixmap(QPixmap a_pxmp)
{
	m_pixmap = std::make_unique<QPixmap>(a_pxmp);
	update();
}

void ChessboardField::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (!m_draggedPiece && m_pixmap)
	{
		QRectF bounding = sceneBoundingRect();		
		if (!m_pxmapItem)
		{
			m_pxmapItem = std::make_unique< QGraphicsPixmapItem>();
			m_scene->addItem(m_pxmapItem.get());
		}
		m_pxmapItem->setPixmap(m_pixmap->scaled(bounding.size().toSize()));
		m_pxmapItem->setPos(bounding.topLeft());
	}
	QGraphicsRectItem::paint(painter, option, widget);
}

void ChessboardField::updateDraggedPos(QGraphicsSceneMouseEvent* event)
{
	if (m_draggedPiece)
	{
		QPointF size = m_draggedPiece->boundingRect().bottomRight() - m_draggedPiece->boundingRect().topLeft();
		m_draggedPiece->setPos(event->scenePos() - size/2);
	}
}

void ChessboardField::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{	
	updateDraggedPos(event);
}

void ChessboardField::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Click" << getText();
	if (m_pixmap)
	{
		// Set m_draggedPiece		
		m_draggedPiece = std::make_unique<QGraphicsPixmapItem>();
		m_scene->addItem(m_draggedPiece.get());
		m_draggedPiece->setPixmap(m_pixmap->scaled(boundingRect().size().toSize()));
		m_draggedPiece->setZValue(1);
		updateDraggedPos(event);

		// TODO: Valide Zuege markieren
	}
}

void ChessboardField::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	m_draggedPiece.reset();
}

