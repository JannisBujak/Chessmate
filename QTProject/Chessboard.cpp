#include "Chessboard.h"
#include <qcolor.h>

#include "Pieces.h"

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
		m_rect_items.push_back(std::make_unique<ChessboardField>('A'+(i%BOARD_WIDTH), 1+i/BOARD_WIDTH, this));
		m_labels.push_back(std::make_unique<QLabel>());				
	}
	for (std::unique_ptr<ChessboardField>& r : m_rect_items)
	{
		scene()->addItem(r.get());
	}
	
	for (std::unique_ptr<QLabel>& l : m_labels)
	{
		scene()->addWidget(l.get());
		l->setVisible(false);
	}

	Piece::glob_ChessPiecesBitmap = create_pixmaps(4, 3, QPixmap(m_filename));
	// m_pxmaps = create_pixmaps(4, 3, QPixmap(m_filename));	
}


ChessboardField* Chessboard::getFieldAt(int x, int y)
{
	return m_rect_items[y * BOARD_WIDTH + x].get();
}

ChessboardField* Chessboard::display_field(int x, int y, const QRectF& a_rect)
{	
	ChessboardField* rect_item = getFieldAt(x, y);

	rect_item->setRect(a_rect);
	if ((x + y) % 2)
		rect_item->setBrush(QColor(238, 238, 228));
	else
		rect_item->setBrush(QColor(234, 182, 118));
	return rect_item;
}

void Chessboard::display_label(int x, int y, const QRectF& a_rect, QPixmap& a_pxmp)
{	
	QLabel* label_item = m_labels[y * BOARD_WIDTH + x].get();
	
	int wTenth = a_rect.width() / 10
		, hTenth = a_rect.height() / 10;
	QRect cpy(a_rect.left() + wTenth
		, a_rect.top() + hTenth
		, a_rect.width() - (2 * wTenth)
		, a_rect.height() - (2 * hTenth)
	);
	
	label_item->setAttribute(Qt::WA_TranslucentBackground);

	label_item->setGeometry(cpy);
	label_item->setPixmap(a_pxmp.scaled(cpy.width(), cpy.height()));

	getFieldAt(x, y)->setPixmap(a_pxmp.scaled(cpy.width(), cpy.height()));
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

			QGraphicsItem* gRect = display_field(x, y, rect);
			int counter = y * BOARD_WIDTH + x;
			std::pair<Piece*, Color> p = m_chessgame.piece_at(x, y);

			QPixmap* pxmp = p.first ? p.first->get_pxmap(p.second) : nullptr;
			if (pxmp)
				display_label(x, y, rect, *pxmp);
		}
	}
	show();
}

void Chessboard::resizeEvent(QResizeEvent* event)
{
	display();
	QGraphicsView::resizeEvent(event);
}

