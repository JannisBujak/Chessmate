#include "Chessboard.h"

Chessboard::Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect)
	: m_application(a_application)
	, QGraphicsView(a_scene)
{
	resize(a_windowrect.width(), a_windowrect.height());
	for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
	{
		m_rect_items.push_back(std::make_unique<QGraphicsRectItem>());
		scene()->addItem(m_rect_items.back().get());
	}
}

void Chessboard::display()
{		
	const size_t width = size().width()
		, height = size().height()
		, xSegSize = width / BOARD_WIDTH
		, ySegSize = height / BOARD_HEIGHT;
		
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			
			QGraphicsRectItem* rect_item = m_rect_items[y * BOARD_WIDTH + x].get();

			QRectF r(x * xSegSize, y * ySegSize, xSegSize, ySegSize);
			rect_item->setRect(r);
			if((x+y) % 2)
				rect_item->setBrush(QColor(234, 182, 118));
			else 
				rect_item->setBrush(QColor(238, 238, 228));
		}
	}	
	show();
}

void Chessboard::print()
{
	using namespace std;
	wcout << "     |";
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		wcout << "  " << (char)('a' + x) << "  |";
	}
	wcout << endl;
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		wcout << "  " << (y + 1) << "  |";
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			std::wcout << "  ";
			auto [piece, color] = m_chessgame.piece_at(x, y);
			if (piece) {
				std::wcout << piece->get_char(color);
			}
			else
				wcout << " ";

			std::wcout << "  |";
		}
		wcout << endl;
	}
}

