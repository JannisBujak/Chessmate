
#include "ChessboardField.h"

#include "Chessgame.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

ChessboardField::ChessboardField(char a_column, char a_row, Chessgame* a_chessgame)
	: m_chessgame(a_chessgame)
	, m_column(a_column)
	, m_row(a_row)
	, m_pxmapItem(nullptr)
{
	qDebug() << "Created field" << getText();
	
	setAcceptDrops(true); 
}

QString ChessboardField::getText()
{
	return QString().asprintf("%c%d", 'A'+m_column, 1+m_row);
}

void ChessboardField::updateDraggedPos(QGraphicsSceneMouseEvent* event)
{
	if (m_draggedPiece)
	{
		QPointF size = m_draggedPiece->boundingRect().bottomRight() - m_draggedPiece->boundingRect().topLeft();
		m_draggedPiece->setPos(event->scenePos() - size/2);
	}
}

QPointF ChessboardField::getBoardPos() const
{
	return QPointF(m_column, m_row);
}

void ChessboardField::setPiece(std::shared_ptr<Piece> a_piece)
{
	this->m_piece = a_piece;
}

std::shared_ptr<Piece> ChessboardField::getPiece()
{
	return m_piece;
}

void ChessboardField::setMarkLegal(bool a_marked)
{
	if (a_marked)
	{
		QPointF size = boundingRect().bottomRight() - boundingRect().topLeft();
		QPointF point = pos() ;
		m_legalMarker = std::make_unique<QGraphicsEllipseItem>(point.x(), point.y(), size.x(), size.y());
		m_legalMarker->setBrush(QColor(50, 200, 50));
		QRectF bounding = sceneBoundingRect();
		m_legalMarker->setPos(bounding.topLeft());
		qDebug() << point;
		// m_legalMarker->setPos(point);
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
	}
	QGraphicsRectItem::paint(painter, option, widget);
}

void ChessboardField::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{	
	updateDraggedPos(event);
}

void ChessboardField::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Click" << getText();
	
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

		// TODO: Valide Zuege markieren
	}
	else 
		m_draggedPiece.reset();
}

void ChessboardField::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{	
	ChessboardField* field_drop = m_chessgame->fieldAtScenePos(event->scenePos());
	
	if (!m_piece || !m_chessgame->isMoveable(m_piece))
		return;

	if (field_drop && field_drop != this)
	{
		QPointF drop_pos = field_drop->getBoardPos();
		int selX = drop_pos.x(), selY = drop_pos.y();

		qDebug() << "From" << getText() << "to" << ((field_drop) ? field_drop->getText() : QString("(%1, %2)").arg(event->scenePos().x()).arg(event->scenePos().y()));

		if (m_piece->move_valid(selX, selY, *m_chessgame))
		{	
			field_drop->cleanPiece();
			field_drop->setPiece(m_piece);
			m_piece->updatePosition(selX, selY);
			m_draggedPiece.reset();
			m_pxmapItem.reset();
			m_piece.reset();
			m_chessgame->confirmMove();
			return;
		}
	}
	qDebug() << "Canceled";
	m_draggedPiece.reset();
}

