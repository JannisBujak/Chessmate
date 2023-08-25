#include "Pieces.h"

#include "Chessgame.h"

namespace Pieces
{
	std::vector<QPixmap> Piece::glob_ChessPiecesBitmap;

	Piece::Piece(int a_col, int a_row, Color a_color)
		: m_column(a_col)
		, m_row(a_row)
		, m_color(a_color)
	{
	}

	QPixmap& Pawn::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[5];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[11];
		};
	}

	bool Pawn::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		int yMov = (m_color == Color::Black) ? 1 : -1;
		// Move up
		if (m_column == a_col)
		{
			if (a_row == m_row + yMov || (m_row == m_origRow && a_row == m_row + 2 * yMov))
			{
				return !a_board.pieceAt(a_col, a_row);
			}
		}
		else if (abs(m_column - a_col) == 1)
		{
			if (a_row == m_row + yMov)
				return a_board.pieceAt(a_col, a_row).get();
		}
		return false;
	}

	Color Piece::getColor()
	{
		return m_color;
	}

	bool Piece::same_pos(int a_col, int a_row)
	{
		return this->m_column == a_col && this->m_row == a_row;
	}

	bool Piece::same_diagonale(int a_col, int a_row) const
	{
		return abs(this->m_column - a_col) == abs(this->m_row - a_row);
	}

	bool Piece::same_row_or_column(int a_col, int a_row) const
	{
		return this->m_column == a_col || this->m_row == a_row;
	}

	bool Piece::pieces_blocking(int a_col, int a_row, const Chessgame& a_board) const
	{
		// Bei Bewegung auf Diagonalen/Reihe/Spalte ueberpruefen, ob was im Weg ist 
		if (same_diagonale(a_col, a_row) || same_row_or_column(a_col, a_row))
		{
			int xMov = (a_col > m_column) ? 1 : ((a_col < m_column) ? -1 : 0)
				, yMov = (a_row > m_row) ? 1 : ((a_row < m_row) ? -1 : 0)
				, mov_range = std::max(abs(a_col - m_column), abs(a_row - m_row));

			for (int i = 1; i < mov_range; i++)
			{
				if (a_board.pieceAt(m_column + xMov * i, m_row + yMov * i))
				{
					qDebug() << "Piece Blocking";
					return true;
				}
			}
		}

		// Nur beim Springer moeglich und der kann immer 
		std::shared_ptr<Piece> piece;
		if (piece = a_board.pieceAt(a_col, a_row))
		{
			if (piece->m_color == m_color)
			{
				// Allie -> cant take			
				qDebug() << "Cant take allie";
				return true;
			}
		}
		return false;
	}

	bool Piece::abandons_king(int a_col, int a_row, Chessgame& a_board) const
	{
		auto allie_king = a_board.getKingFromList(m_color);		
		auto enemy_pieces = a_board.getListOfColor((m_color == Color::Black) ? Color::White : Color::Black);

		return false;
	}

	void Piece::updatePosition(int a_col, int a_row)
	{
		this->m_column = a_col;
		this->m_row = a_row;
	}

	bool Piece::move_valid(int a_col, int a_row, Chessgame& a_board)
	{
		bool a, b, c, d;
		a = !same_pos(a_col, a_row);
		b = piece_moveable(a_col, a_row, a_board);
		c = !pieces_blocking(a_col, a_row, a_board);
		d = !abandons_king(a_col, a_row, a_board);
		return a && b && c && d;
	}

	QPointF Piece::getBoardPos() const
	{
		return QPoint(m_column, m_row);
	}

	Pawn::Pawn(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
		, m_origRow(a_row)
	{
	}

	Rook::Rook(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QPixmap& Rook::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[2];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[8];
		};
	}

	bool Rook::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		return same_row_or_column(a_col, a_row);
	}

	Knight::Knight(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QPixmap& Knight::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[4];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[10];
		};
	}

	bool Knight::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		int XMov = abs(a_col - m_column)
			, yMov = abs(a_row - m_row);
		bool a = (XMov + yMov == 3);
		bool b = (abs(XMov - yMov) == 1);;
		return a && b;
	}

	Bishop::Bishop(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QPixmap& Bishop::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[3];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[9];
		};
	}

	bool Bishop::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		return same_diagonale(a_col, a_row);
	}

	Queen::Queen(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QPixmap& Queen::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[1];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[7];
		};
	}

	bool Queen::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		return same_row_or_column(a_col, a_row) || same_diagonale(a_col, a_row);
	}

	King::King(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QPixmap& King::get_pxmap()
	{
		switch (m_color)
		{
		case  Color::White:
			return glob_ChessPiecesBitmap[0];
		case  Color::Black:
		default:
			return glob_ChessPiecesBitmap[6];
		};
	}

	bool King::piece_moveable(int a_col, int a_row, const Chessgame& a_board) const
	{
		return (abs(a_col - m_column) <= 1) && (abs(a_row - m_row) <= 1);
	}
}

