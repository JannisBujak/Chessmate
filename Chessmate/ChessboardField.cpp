
#include "ChessboardField.h"

#include "ChessGameVisualisation.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

ChessboardField::ChessboardField(char a_column, char a_row, ChessGameVisualisation* a_chessgame)
	: m_chessgame(a_chessgame)
	, m_column(a_column)
	, m_row(a_row)
	, m_pxmapItem(nullptr)
{
	setAcceptDrops(true); 
}

QString ChessboardField::getText()
{
	return ChessGame::chessposToString(QPoint(m_column, m_row));
}

void ChessboardField::updateDraggedPos(QGraphicsSceneMouseEvent* event)
{
	if (m_draggedPiece)
	{
		QPointF size = m_draggedPiece->boundingRect().bottomRight() - m_draggedPiece->boundingRect().topLeft();
		m_draggedPiece->setPos(event->scenePos() - size/2);
	}
}

QPoint ChessboardField::getBoardPos() const
{
	return QPoint(m_column, m_row);
}

void ChessboardField::setPiece(std::shared_ptr<Pieces::Piece> a_piece)
{
	this->m_piece = a_piece;
	if (!this->m_piece)
		m_pxmapItem.reset();
}

std::shared_ptr<Pieces::Piece> ChessboardField::getPiece()
{
	return m_piece;
}

void ChessboardField::setMarkLegal(bool a_marked)
{
	if (a_marked)
	{
		QPointF size = boundingRect().bottomRight() - boundingRect().topLeft();
		QPointF point = pos();
		m_legalMarker = std::make_unique<QGraphicsEllipseItem>(point.x(), point.y(), size.x(), size.y(), this);
		m_legalMarker->setBrush(QColor(50, 200, 50));
		QRectF bounding = sceneBoundingRect();
		m_legalMarker->setPos(bounding.topLeft());
		m_legalMarker->show();
	}
	else {
		m_legalMarker.reset();
	}
}

void ChessboardField::cleanPiece()
{
	if (m_piece)
	{
		m_chessgame->cleanPiece(m_piece);
		m_piece.reset();		
		this->show();
	}
}

void ChessboardField::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{	
	if (!m_draggedPiece && m_piece)
	{
		QPixmap pixmap = m_piece->get_pxmap();
		QRectF bounding = sceneBoundingRect();
		if (!m_pxmapItem)
		{
			m_pxmapItem = std::make_unique< QGraphicsPixmapItem>();
			m_chessgame->scene()->addItem(m_pxmapItem.get());
		}
		m_pxmapItem->setPixmap(pixmap.scaled(bounding.size().toSize()));
		m_pxmapItem->setPos(bounding.topLeft());
		m_pxmapItem->show();
	}
	else if(m_pxmapItem)
	{
		m_pxmapItem->hide();
	}
	QGraphicsRectItem::paint(painter, option, widget);
}

void ChessboardField::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{	
	updateDraggedPos(event);
}

void ChessboardField::mousePressEvent(QGraphicsSceneMouseEvent* event)
{	
	if (m_piece && m_chessgame->isMoveable(m_piece))
	{
		QPixmap pixmap = m_piece->get_pxmap();
		// Set m_draggedPiece		
		m_draggedPiece = std::make_unique<QGraphicsPixmapItem>();
		m_pxmapItem.reset();
		m_chessgame->scene()->addItem(m_draggedPiece.get());
		m_draggedPiece->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
		m_draggedPiece->setZValue(1);
		updateDraggedPos(event);
		m_chessgame->markLegalMoves(m_piece);
	}
	else 
		m_draggedPiece.reset();
}

void ChessboardField::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{	
	ChessboardField* field_drop = m_chessgame->fieldAtScenePos(event->scenePos());
	qDebug() << "From" << getText() << "to" << ((field_drop) ? field_drop->getText() : QString("(%1, %2)").arg(event->scenePos().x()).arg(event->scenePos().y()));
	
	// Markierung legaler moves entfernen
	if (m_chessgame->handlePieceDraggedFromTo(this, field_drop))
	{
		this->m_piece.reset();
		m_pxmapItem.reset();
	}else{
		qDebug() << "Canceled";
	}
	m_draggedPiece.reset();
}

