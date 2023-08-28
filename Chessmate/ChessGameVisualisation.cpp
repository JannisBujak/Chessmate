#include "ChessGameVisualisation.h"
#include <qcolor.h>

ChessGame::ChessGame(QObject* parent)
	: QObject(parent)
{
	init();
}

ChessGame::ChessGame(const ChessGame& other)
	: m_playingColor(other.m_playingColor)
{
	for (auto w : other.white)	
		white.push_back(std::shared_ptr< Pieces::Piece>(w->clone()));
	
	for (auto b : other.black)
		black.push_back(std::shared_ptr<Pieces::Piece>(b->clone()));
}

Color ChessGame::playingColor()
{
	return m_playingColor;
}

void ChessGame::togglePlayingColor()
{
	setPlayingColor((playingColor() == Color::Black) ? Color::White : Color::Black);
}

void ChessGame::setPlayingColor(Color a_playingColor)
{
	m_playingColor = a_playingColor;
	emit playingColorChanged(m_playingColor);
}

void ChessGame::fillBackrow(Color a_color, int a_col)
{
	addPiece	<Pieces::Rook>(a_color, 0, a_col);
	addPiece	<Pieces::Knight>(a_color, 1, a_col);
	addPiece	<Pieces::Bishop>(a_color, 2, a_col);
	addPiece	<Pieces::Queen>(a_color, 3, a_col);
	addPiece	<Pieces::King>(a_color, 4, a_col);
	addPiece	<Pieces::Bishop>(a_color, 5, a_col);
	addPiece	<Pieces::Knight>(a_color, 6, a_col);
	addPiece	<Pieces::Rook>(a_color, 7, a_col);
}

void ChessGame::removeAllPieces()
{
	if (!white.empty())
		white.clear();
	if (!black.empty())
		black.clear();
}

bool ChessGame::isMoveable(std::shared_ptr<Pieces::Piece> a_piece)
{
	auto pc = a_piece->getColor();
	return playingColor() == pc;
}

std::shared_ptr<Pieces::Piece> ChessGame::pieceAt(int x, int y) const
{
	for (std::shared_ptr<Pieces::Piece> w : white)
	{
		if (w->same_pos(x, y))
		{
			return w;
		}
	}

	for (std::shared_ptr<Pieces::Piece> b : black)
	{
		if (b->same_pos(x, y))
		{
			return b;
		}
	}
	return std::shared_ptr<Pieces::Piece>();
}

Pieces::King* ChessGame::getKingFromList(std::vector < std::shared_ptr<Pieces::Piece>> a_ColoredPieces)
{
	Pieces::King* king;
	for (auto e : a_ColoredPieces)
		if (king = dynamic_cast<Pieces::King*>(e.get()))
			return king;

	return nullptr;
}

Pieces::King* ChessGame::getKingFromList(Color a_color)
{
	return getKingFromList((a_color == Color::Black) ? black : white);
}

const std::vector<std::shared_ptr<Pieces::Piece>> ChessGame::getListOfColor(Color a_color) const
{
	return (a_color == Color::Black) ? black : white;
}

std::vector<std::shared_ptr<Pieces::Piece>> ChessGame::getListOfColor(Color a_color)
{
	return (a_color == Color::Black) ? black : white;
}

std::vector<std::shared_ptr<Pieces::Piece>> ChessGame::getListOfPieces()
{
	std::vector<std::shared_ptr<Pieces::Piece>> all_pieces = black;
	all_pieces.insert(all_pieces.end(), white.begin(), white.end());

	return all_pieces;
}

void ChessGame::checkForWin()
{
	// First get the two kings
	Pieces::King* bk = getKingFromList(black)
		, * wk = getKingFromList(white);
	Q_ASSERT(bk || wk);
	if (!bk)
	{
		qDebug() << "No black King";
		emit playerWon(Color::White);
	}
	else if (!wk)
	{
		qDebug() << "No white King";
		emit playerWon(Color::Black);
	}
	else
	{
		Pieces::King* checked_king;
		std::vector<std::shared_ptr<Pieces::Piece>> opposing_pieces;
		// Check if players king is under Attack
		checked_king = (m_playingColor == Color::White) ? wk : bk;
		opposing_pieces = (m_playingColor == Color::White) ? black : white;

		auto kingPos = checked_king->getBoardPos();

		for (auto opposing_piece : opposing_pieces)
		{
			if (opposing_piece->move_valid(kingPos.x(), kingPos.y(), *this))
			{
				qDebug() << ((m_playingColor == Color::White) ? QString("White") : QString("Black")) << "King checked";
			}
		}
	}
}

void ChessGame::confirmMove()
{
	// Toggles playing color
	togglePlayingColor();

	// Check if player is under attack and can defend
	checkForWin();
}

void ChessGame::cleanPiece(std::shared_ptr<Pieces::Piece> a_piece)
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

void ChessGame::init()
{
	removeAllPieces();
	setPlayingColor(Color::White);

	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		addPiece <Pieces::Pawn> (Color::White, x, 6);
		addPiece <Pieces::Pawn> (Color::Black, x, 1);
	}
	
	fillBackrow(Color::Black, 0);
	fillBackrow(Color::White, 7);
}

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

		if (piece->move_valid(selX, selY, m_ChessGame))
		{
			drag_to->cleanPiece();
			drag_to->setPiece(piece);
			piece->updatePosition(selX, selY);
            m_ChessGame.confirmMove();
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
    return m_ChessGame.isMoveable(a_piece);
}


