
#include "ChessboardField.h"

#include "Chessboard.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

ChessboardField::ChessboardField(char a_column, char a_row, Chessboard* a_chessboard)
	: m_chessboard(a_chessboard)
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

void ChessboardField::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{	
	if (!m_draggedPiece && m_piece)
	{
		QPixmap pixmap = m_piece->get_pxmap();
		QRectF bounding = sceneBoundingRect();		
		if (!m_pxmapItem)
		{
			m_pxmapItem = std::make_unique< QGraphicsPixmapItem>();
			m_chessboard->scene()->addItem(m_pxmapItem.get());
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
	
	if (m_piece)
	{
		QPixmap pixmap = m_piece->get_pxmap();
		// Set m_draggedPiece		
		m_draggedPiece = std::make_unique<QGraphicsPixmapItem>();
		m_pxmapItem.reset();
		m_chessboard->scene()->addItem(m_draggedPiece.get());
		m_draggedPiece->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
		m_draggedPiece->setZValue(1);
		updateDraggedPos(event);

		// TODO: Valide Zuege markieren
	}
}

void ChessboardField::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	// TODO: Komplett neu 

	auto piece = this->m_piece;
	if (!piece)
		return;

	ChessboardField* field_drop = m_chessboard->fieldAtScenePos(event->scenePos());
	
	QPointF drop_pos = field_drop->getBoardPos();
	
	qDebug() << "From" << getText() << "to" << ((field_drop) ? field_drop->getText() : QString("(%1, %2)").arg(event->scenePos().x()).arg(event->scenePos().y()));
	if (field_drop != this)
	{
		if (piece->move_valid(drop_pos.x(), drop_pos.y(), *m_chessboard))
		{
			field_drop->setPiece(m_piece);
			m_draggedPiece.reset();
			m_pxmapItem.reset();
			m_piece.reset();
		}
	}
	else {
		// Invalid move 
		m_draggedPiece.reset();
	}
}

