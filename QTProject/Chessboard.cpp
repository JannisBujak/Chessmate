#include "Chessboard.h"

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

			pxmaps.push_back(a_glob_pxmp.copy(cutout_rect));
		}
	}
	return pxmaps;
}

Chessboard::Chessboard(QApplication& a_application, QGraphicsScene* a_scene, QSize a_windowrect)
	: m_application(a_application)
	, QGraphicsView(a_scene)
{
	resize(a_windowrect.width(), a_windowrect.height());
	for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
	{
		m_rect_items.push_back(std::make_unique<QGraphicsRectItem>());
		m_labels.push_back(std::make_unique<QLabel>());
		m_images.push_back(std::make_unique<QImage>());
	}
	for (std::unique_ptr<QGraphicsRectItem>& r : m_rect_items)
	{
		scene()->addItem(r.get());
	}
	
	for (std::unique_ptr<QLabel>& l : m_labels)
	{
		scene()->addWidget(l.get());
	}
	
	m_pxmaps = create_pixmaps(4, 3, QPixmap(m_filename));
	
}


void Chessboard::display_rect(int x, int y, const QRectF& a_rect)
{
	
	QGraphicsRectItem* rect_item = m_rect_items[y * BOARD_WIDTH + x].get();

	rect_item->setRect(a_rect);
	if ((x + y) % 2)
		rect_item->setBrush(QColor(238, 238, 228));
	else
		rect_item->setBrush(QColor(234, 182, 118));

}

void Chessboard::display_label(int x, int y, const QRectF& a_rect, QPixmap& a_pxmp)
{	
	QLabel* label_item = m_labels[y * BOARD_WIDTH + x].get();
	
	int wTenth = a_rect.width() / 3
		, hTenth = a_rect.height() / 3;
	QRect cpy(a_rect.left() + wTenth
		, a_rect.top() + hTenth
		, a_rect.width() - (2 * wTenth)
		, a_rect.height() - (2 * hTenth)
	);
	
	label_item->setGeometry(cpy);
	label_item->setPixmap(a_pxmp.scaled(cpy.width(), cpy.height()));
}

void Chessboard::display()
{	
	const size_t width = size().width()
		, height = size().height()
		, xSegSize = width / BOARD_WIDTH
		, ySegSize = height / BOARD_HEIGHT;	
	
	QRectF rect;
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			rect = QRectF(x * xSegSize, y * ySegSize, xSegSize, ySegSize);

			display_rect(x, y, rect);
			int counter = y * BOARD_WIDTH + x;
			display_label(x, y, rect, m_pxmaps[counter % m_pxmaps.size()]);
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

void Chessboard::resizeEvent(QResizeEvent* event)
{
	display();
	QGraphicsView::resizeEvent(event);
}

