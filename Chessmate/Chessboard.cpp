#include "Chessboard.h"
#include <qcolor.h>

std::vector<QPixmap> Chessboard::create_pixmaps(int a_xSectors, int a_ySectors, const QPixmap& a_glob_pxmp)
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

Chessboard::Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect)
	: m_application(a_application)
	, QGraphicsView(a_scene)
{
	resize(a_windowrect.width(), a_windowrect.height());
	
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		
	for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
	{
		m_rect_items.push_back(std::make_unique<ChessboardField>(i%BOARD_WIDTH, i/BOARD_WIDTH, this));		
	}
	for (std::unique_ptr<ChessboardField>& r : m_rect_items)
	{
		scene()->addItem(r.get());
	}	

	Piece::glob_ChessPiecesBitmap = create_pixmaps(4, 3, QPixmap(m_filename));
	// m_pxmaps = create_pixmaps(4, 3, QPixmap(m_filename));	
}

void Chessboard::init()
{
	/*auto addPiece = [&] <typename T> (std::vector<std::shared_ptr<Piece>>&vec, int a_col, int a_row)
	{
		vec.push_back(std::make_shared<T>(a_col, a_row));
	};*/

	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		addPiece <Pawn> (white, x, 6);
		white.push_back(std::make_unique<Pawn>(x, 6));
		black.push_back(std::make_unique<Pawn>(x, 1));
	}
	/*
	auto fill_backrow = [](std::vector<std::unique_ptr<Piece>>& a_team, int col)
	{
		a_team.push_back(std::make_unique<Rook>(0, col));
		a_team.push_back(std::make_unique<Knight>(1, col));
		a_team.push_back(std::make_unique<Bishop>(2, col));
		a_team.push_back(std::make_unique<Queen>(3, col));
		a_team.push_back(std::make_unique<King>(4, col));
		a_team.push_back(std::make_unique<Bishop>(5, col));
		a_team.push_back(std::make_unique<Knight>(6, col));
		a_team.push_back(std::make_unique<Rook>(7, col));
	};
	fill_backrow(black, 0);
	fill_backrow(white, 7);*/

	// R K B Q K B K R
}


ChessboardField* Chessboard::fieldAt(int x, int y)
{
	return m_rect_items[y * BOARD_WIDTH + x].get();	
}

ChessboardField* Chessboard::fieldAtScenePos(QPointF a_scPos)
{
	for(int i = 0; i < m_rect_items.size(); i++)
	{
		if(m_rect_items[i]->sceneBoundingRect().contains(a_scPos))
		{
			return m_rect_items[i].get();
		}
	}
	return nullptr;
}


ChessboardField* Chessboard::display_field(int x, int y, const QRectF& a_rect)
{	
	ChessboardField* rect_item = fieldAt(x, y);

	rect_item->setRect(a_rect);
	if ((x + y) % 2)
		rect_item->setBrush(QColor(238, 238, 228));
	else
		rect_item->setBrush(QColor(234, 182, 118));
	return rect_item;
}

void Chessboard::display_label(int x, int y, const QRectF& a_rect, QPixmap& a_pxmp)
{	
	int wTenth = a_rect.width() / 10
		, hTenth = a_rect.height() / 10;
	QRect cpy(a_rect.left() + wTenth
		, a_rect.top() + hTenth
		, a_rect.width() - (2 * wTenth)
		, a_rect.height() - (2 * hTenth)
	);
	
	fieldAt(x, y)->setPixmap(a_pxmp.scaled(cpy.width(), cpy.height()));
}

void Chessboard::display()
{	
	const size_t width = size().width()
		, height = size().height()
		, xSegSize = width / BOARD_WIDTH
		, ySegSize = height / BOARD_HEIGHT;	
	
	QRectF rect;

	// TODO: Neu 
	/*
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			rect = QRectF(x * xSegSize, y * ySegSize, xSegSize, ySegSize);

			QGraphicsItem* gRect = display_field(x, y, rect);
			int counter = y * BOARD_WIDTH + x;
			
			std::pair<Piece*, Color> p = m_chessgame.piece_at(x, y);

			QPixmap* pxmp = p.first ? p.first->get_pxmap(p.second) : nullptr;
			if (pxmp)
				display_label(x, y, rect, *pxmp);			
		}
	}*/
	show();
}

void Chessboard::resizeEvent(QResizeEvent* event)
{
	display();
	QGraphicsView::resizeEvent(event);
}

