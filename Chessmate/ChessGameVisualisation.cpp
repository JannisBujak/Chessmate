#include "ChessGameVisualisation.h"
#include <qcolor.h>

std::vector<QPixmap> ChessGameVisualisation::create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp)
{
	std::vector<QPixmap> pxmaps;
	int xSectorSize = a_glob_pxmp.width() / a_xSectors
		, ySectorSize = a_glob_pxmp.height() / a_ySectors;
	
	for (int y = 0; y < a_ySectors; y++)
	{
		for (int x = 0; x < a_xSectors; x++)
		{
			QRect cutout_rect(x * xSectorSize, y * ySectorSize, xSectorSize, ySectorSize);
			QPixmap& last = pxmaps.emplace_back();
			last = a_glob_pxmp.copy(cutout_rect);
		}
	}
	return pxmaps;
}



ChessGameVisualisation::ChessGameVisualisation(QGraphicsScene* a_scene)
	: QGraphicsView(a_scene)
	, m_infoButton(std::make_shared<QGraphicsTextItem>())
{	
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		
	for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
	{
		m_fields.push_back(std::make_shared<ChessboardField>(i%BOARD_WIDTH, i/BOARD_WIDTH, this));		
	}
	for (std::shared_ptr<ChessboardField>& r : m_fields)
	{
		scene()->addItem(r.get());
	}	

	Pieces::Piece::glob_ChessPiecesBitmap = create_pixmaps(4, 3, QPixmap(m_filename));
}

void ChessGameVisualisation::removeAllPieces()
{
    m_ChessGame.removeAllPieces();
	
	for(auto& field : m_fields)
	{
		field->setPiece();
	}
}

void ChessGameVisualisation::init()
{
    for(const auto& field : m_fields)
        field->setPiece();
    m_ChessGame.init();
	auto pieces = m_ChessGame.getListOfPieces();
	for (auto p : pieces)
	{
		auto ppos = p->getBoardPos();
		fieldAt(ppos.x(), ppos.y())->setPiece(p);
	}
	// R K B Q K B K R
	display();
}

ChessboardField* ChessGameVisualisation::fieldAt(int x, int y)
{
	return m_fields[y * BOARD_WIDTH + x].get();	
}

ChessboardField* ChessGameVisualisation::fieldAt(QPoint point)
{
	return fieldAt(point.x(), point.y());
}

ChessboardField* ChessGameVisualisation::fieldAtScenePos(QPointF a_scPos)
{
	for(int i = 0; i < m_fields.size(); i++)
	{
		if(m_fields[i]->sceneBoundingRect().contains(a_scPos))
		{
			return m_fields[i].get();
		}
	}
	return nullptr;
}

ChessboardField* ChessGameVisualisation::display_field(int x, int y, const QRectF& a_rect)
{	
	ChessboardField* field = fieldAt(x, y);

	field->setRect(a_rect);
	if ((x + y) % 2)
		field->setBrush(QColor(238, 238, 228));
	else
		field->setBrush(QColor(234, 182, 118));
		
	std::shared_ptr<Pieces::Piece> piece;
	if (piece = field->getPiece())
	{
		display_label(x, y, a_rect, piece->get_pxmap());
	}
	
	return field;
}

void ChessGameVisualisation::display_label(int x, int y, const QRectF& a_rect, const QPixmap& a_pxmp)
{	
	int wTenth = a_rect.width() / 10
		, hTenth = a_rect.height() / 10;
	QRect cpy(a_rect.left() + wTenth
		, a_rect.top() + hTenth
		, a_rect.width() - (2 * wTenth)
		, a_rect.height() - (2 * hTenth)
	);
	
	// fieldAt(x, y)->setPixmap(a_pxmp.scaled(cpy.width(), cpy.height()));
}

void ChessGameVisualisation::display()
{
    using namespace Pieces;
	const size_t width = size().width()
		, height = size().height()
		, xSegSize = width / BOARD_WIDTH
		, ySegSize = height / BOARD_HEIGHT;	
	
	QRectF rect;

	// m_infoButton->setRect(0, 0, 200, 200);
	m_infoButton->setPlainText(QString("%1 to move").arg((m_ChessGame.playingColor() == Color::White) ? QString("White") : QString("Black")));
	
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			rect = QRectF(x * xSegSize, y * ySegSize, xSegSize, ySegSize);

			QGraphicsItem* gRect = display_field(x, y, rect);
			int counter = y * BOARD_WIDTH + x;
		}
	}
}

void ChessGameVisualisation::markLegalMoves(std::shared_ptr<Pieces::Piece> a_piece)
{
#if MARK_MOVES
	std::vector< std::shared_ptr<ChessboardField>> legal_fields;
	for (std::shared_ptr<ChessboardField> field : m_fields)
	{
		auto [fieldX, fieldY] = field->getBoardPos();
		if (a_piece->move_valid(fieldX, fieldY, m_ChessGame))
		{
			legal_fields.push_back(field);
		}
	}

	for (auto field : legal_fields)
		field->setMarkLegal(true);
#endif
}

void ChessGameVisualisation::markNoMoves()
{
	for (std::shared_ptr<ChessboardField> field : m_fields)
	{
		field->setMarkLegal(false);		
	}
}

const ChessGame *ChessGameVisualisation::getChessGame() {
    return &m_ChessGame;
}

void ChessGameVisualisation::resizeEvent(QResizeEvent* event)
{
	display();
	QGraphicsView::resizeEvent(event);
}

bool ChessGameVisualisation::handlePieceDraggedFromTo(ChessboardField* drag_from, ChessboardField* drag_to)
{
	// Markierung legaler moves entfernen
	markNoMoves();

	if (!drag_from->getPiece() || !m_ChessGame.isMoveable(drag_from->getPiece()))
		return false;

	if (drag_to && drag_from != drag_to)
	{
		QPointF drop_pos = drag_to->getBoardPos();
		int selX = drop_pos.x(), selY = drop_pos.y();

		auto piece = drag_from->getPiece();

		// Use to get the position en passant would take 
		std::shared_ptr<QPoint> sideeffectPos;

		if (piece->move_valid(selX, selY, m_ChessGame, &sideeffectPos))
		{
			drag_to->cleanPiece();
			if (sideeffectPos)
			{
				ChessboardField* sideeffectField;
				if (sideeffectField = fieldAt(*sideeffectPos))
				{		
					if (piece->getColor() == sideeffectField->getPiece()->getColor())
					{
						 // Another piece of same color moved -> Castle
						auto rook = dynamic_cast<Pieces::Rook*>(sideeffectField->getPiece().get());

						QPoint new_rookpos = QPoint(
							(selX + piece->getBoardPos().x()) / 2,
							(selY + piece->getBoardPos().y()) / 2);
						rook->updatePosition(new_rookpos);
						
						fieldAt(new_rookpos)->setPiece(sideeffectField->getPiece());
						sideeffectField->setPiece();
					}
					else
					{
						// Another piece of other color moved -> En passant
						sideeffectField->cleanPiece();
					}
				}
			}		
			drag_to->setPiece(piece);
			piece->updatePosition(selX, selY);
            m_ChessGame.confirmMove(ChessGame::History(piece, piece->getBoardPos(), drop_pos.toPoint()));
			return true;
		}
	}
	return false;
}

void ChessGameVisualisation::cleanPiece(std::shared_ptr<Pieces::Piece> a_piece)
{
    m_ChessGame.cleanPiece(a_piece);
}

bool ChessGameVisualisation::isMoveable(std::shared_ptr<Pieces::Piece> a_piece)
{
    return !m_ChessGame.gameOver() && m_ChessGame.isMoveable(a_piece);
}


