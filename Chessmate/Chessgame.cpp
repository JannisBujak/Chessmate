#include "Chessgame.h"
#include <qcolor.h>

std::vector<QPixmap> Chessgame::create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp)
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

Chessgame::Chessgame(QGraphicsScene* a_scene)
	: QGraphicsView(a_scene)
	, m_playingColor(Color::White)
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

	Piece::glob_ChessPiecesBitmap = create_pixmaps(4, 3, QPixmap(m_filename));
	
	init();
}

void Chessgame::fillBackrow(Color a_color, int a_col)
{	
	addPiece	<Rook>		(a_color, 0, a_col);
	addPiece	<Knight>	(a_color, 1, a_col);
	addPiece	<Bishop>	(a_color, 2, a_col);
	addPiece	<Queen>		(a_color, 3, a_col);
	addPiece	<King>		(a_color, 4, a_col);
	addPiece	<Bishop>	(a_color, 5, a_col);
	addPiece	<Knight>	(a_color, 6, a_col);
	addPiece	<Rook>		(a_color, 7, a_col);	
}

void Chessgame::init()
{
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		addPiece <Pawn> (Color::White, x, 6);
		addPiece <Pawn> (Color::Black, x, 1);
	}
	
	fillBackrow(Color::Black, 0);
	fillBackrow(Color::White, 7);

	// R K B Q K B K R
}

std::shared_ptr<Piece> Chessgame::pieceAt(int x, int y) const
{
	for (std::shared_ptr<Piece> w : white)
	{
		if (w->same_pos(x, y))
		{
			return w;
		}
	}

	for (std::shared_ptr<Piece> b : black)
	{
		if (b->same_pos(x, y))
		{
			return b;
		}
	}
	return std::shared_ptr<Piece>();
}

ChessboardField* Chessgame::fieldAt(int x, int y)
{
	return m_fields[y * BOARD_WIDTH + x].get();	
}

ChessboardField* Chessgame::fieldAtScenePos(QPointF a_scPos)
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

ChessboardField* Chessgame::display_field(int x, int y, const QRectF& a_rect)
{	
	ChessboardField* field = fieldAt(x, y);

	field->setRect(a_rect);
	if ((x + y) % 2)
		field->setBrush(QColor(238, 238, 228));
	else
		field->setBrush(QColor(234, 182, 118));
		
	std::shared_ptr<Piece> piece;
	if (piece = field->getPiece())
	{
		display_label(x, y, a_rect, piece->get_pxmap());
	}
	
	return field;
}

void Chessgame::display_label(int x, int y, const QRectF& a_rect, const QPixmap& a_pxmp)
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

void Chessgame::display()
{	
	const size_t width = size().width()
		, height = size().height()
		, xSegSize = width / BOARD_WIDTH
		, ySegSize = height / BOARD_HEIGHT;	
	
	QRectF rect;

	// m_infoButton->setRect(0, 0, 200, 200);
	m_infoButton->setPlainText(QString("%1 to move").arg((m_playingColor == Color::White) ? QString("White") : QString("Black")));
	
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			rect = QRectF(x * xSegSize, y * ySegSize, xSegSize, ySegSize);

			QGraphicsItem* gRect = display_field(x, y, rect);
			int counter = y * BOARD_WIDTH + x;
		}
	}
	show();
}

void Chessgame::markLegalMoves(std::shared_ptr<Piece> a_piece)
{
	for (std::shared_ptr<ChessboardField> field : m_fields)
	{
		auto [fieldX, fieldY] = field->getBoardPos();
		if(a_piece->move_valid(fieldX, fieldY, *this))
		{
			field->setMarkLegal(true);
		}
	}
	qDebug() << " ";
}

void Chessgame::markNoMoves(std::shared_ptr<Piece> a_piece)
{
	for (std::shared_ptr<ChessboardField> field : m_fields)
	{
		field->setMarkLegal(false);		
	}
}

bool Chessgame::isMoveable(std::shared_ptr<Piece> a_piece)
{
	auto pc = a_piece->getColor();
	return m_playingColor == pc;
}

void Chessgame::confirmMove()
{
	// Toggles playing color
	m_playingColor = (m_playingColor == Color::White) ? Color::Black : Color::White;
}

void Chessgame::cleanPiece(std::shared_ptr<Piece> a_piece)
{
	if (a_piece->getColor() == Color::White)
	{
		deleteElementFromList(a_piece, white);
	}
	else 
	{
		deleteElementFromList(a_piece, black);
	}
}

void Chessgame::resizeEvent(QResizeEvent* event)
{
	display();
	QGraphicsView::resizeEvent(event);
}

QSizeF Chessgame::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	return QSizeF();
}

