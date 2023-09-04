#include "Pieces.h"

#include "ChessGameVisualisation.h"

namespace Pieces
{
    Color oppositeColor(Color a_color)
    {
        switch(a_color)
        {
            case Color::Black:
                return Color::White;
            case Color::White:
                return Color::Black;
            default:
                return Color::None;
        }
    }

	std::vector<QPixmap> Piece::glob_ChessPiecesBitmap;

	Piece::Piece(int a_col, int a_row, Color a_color)
		: m_column(a_col)
		, m_row(a_row)
        , m_timesMoved(0)
		, m_color(a_color)
	{
	}

	QString Pawn::piece_name() const
	{
		return "Pawn";
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
		}
	}

	bool Pawn::en_passant_counter_possible(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const 
	{
		Pieces::Pawn* p;
		if ((p = dynamic_cast<Pieces::Pawn*>(a_board.pieceAt(a_col, m_row).get())) && (m_color != p->getColor()))
		{
			// en passant counter
			if ((p->timesMoved() == 1) && (abs(p->m_row - p->m_origRow) >= 2))
			{
				// Check if last move was to QPoint(a_col, m_row), En passant-counter is only available for 1 round
				auto history = a_board.getHistory();
				bool en_passant_counter_possible = !history.empty() && history.back().to == QPoint(a_col, m_row);
				if (en_passant_counter_possible)
				{
					if (a_beatenPoint)
						a_beatenPoint->reset(new QPoint(a_col, m_row));
				}
				return en_passant_counter_possible;
			}
		}
		return false;
	}

	bool Pawn::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
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
            Pieces::Pawn* p;
			if (a_row == m_row + yMov)
            {
                if (a_board.pieceAt(a_col, a_row).get())
                {
                    return true;
                }
                else if (en_passant_counter_possible(a_col, a_row, a_board, a_beatenPoint))
                {
                    // en passant counter
					return true;
                }
            }
		}
		return false;
	}

	Piece* Pawn::clone() const
	{
		return new Pawn(*this);
	}

	Color Piece::getColor() const
	{
		return m_color;
	}

    int Piece::timesMoved() const
    {
        return m_timesMoved;
    }

	bool Piece::same_pos(int a_col, int a_row) const
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

	bool Piece::pieces_blocking(int a_col, int a_row, const ChessGame& a_board) const
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
        piece = a_board.pieceAt(a_col, a_row);
        if (piece)
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

	bool Piece::abandons_king(int a_col, int a_row, const ChessGame& a_board) const
	{
		ChessGame copy = a_board;

		auto this_piece = copy.pieceAt(m_column, m_row);
		this_piece->m_column = a_col;
		this_piece->m_row = a_row;

        auto king = copy.getKingFromList(this->m_color);
        if(!king)
            return true;

        auto kingPos = king->getBoardPos();

        auto& enemy_pieces = copy.getListOfColor(oppositeColor(m_color));

        for ( auto it = enemy_pieces.begin(); it != enemy_pieces.end(); ++it)
        {
            if(it->get()->same_pos(a_col, a_row))
            {
                enemy_pieces.erase(it);
                break;
            }
        }

		for (const auto& enemy : enemy_pieces)
		{
			if (enemy->move_valid(kingPos.x(), kingPos.y(), copy))
			{
				return true;
			}
		}
		return false;
	}

	void Piece::updatePosition(int a_col, int a_row)
	{
		this->m_column = a_col;
		this->m_row = a_row;
        this->m_timesMoved++;
	}

	bool Piece::move_valid(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint)
	{
		return !same_pos(a_col, a_row)
			&& piece_moveable(a_col, a_row, a_board, a_beatenPoint)
			&& !pieces_blocking(a_col, a_row, a_board)
			&& !abandons_king(a_col, a_row, a_board);
	}

	QPoint Piece::getBoardPos() const
	{
		return QPoint(m_column, m_row);
	}

    bool Piece::isAttacked(const ChessGame& a_board) const {
        auto oc = oppositeColor(m_color);
        const auto& enemyPieces = a_board.getListOfColor(oc);
        for(const auto& enemyPiece : enemyPieces)
        {
            if(enemyPiece->move_valid(m_column, m_row, a_board))
                return true;
        }
        return false;
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

	QString Rook::piece_name() const
	{
		return "Rook";
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
		}
	}

	bool Rook::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
	{
		return same_row_or_column(a_col, a_row);
	}

	Piece* Rook::clone() const
	{
		return new Rook(*this);;
	}

	Knight::Knight(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QString Knight::piece_name() const
	{
		return "Knight";
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

	bool Knight::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
	{
		int XMov = abs(a_col - m_column)
			, yMov = abs(a_row - m_row);
		bool a = (XMov + yMov == 3);
		bool b = (abs(XMov - yMov) == 1);;
		return a && b;
	}

	Piece* Knight::clone() const
	{
		return new Knight(*this);
	}

	Bishop::Bishop(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QString Bishop::piece_name() const
	{
		return "Bishop";
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

	bool Bishop::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
	{
		return same_diagonale(a_col, a_row);
	}

	Piece* Bishop::clone() const
	{
		return new Bishop(*this);
	}

	Queen::Queen(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QString Queen::piece_name() const
	{
		return "Queen";
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

	bool Queen::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
	{
		return same_row_or_column(a_col, a_row) || same_diagonale(a_col, a_row);
	}

	Piece* Queen::clone() const
	{
		return new Queen(*this);
	}

	King::King(int a_col, int a_row, Color a_color)
		: Piece(a_col, a_row, a_color)
	{
	}

	QString King::piece_name() const
	{
		return "King";
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

	bool King::piece_moveable(int a_col, int a_row, const ChessGame& a_board, std::shared_ptr<QPoint>* a_beatenPoint) const
	{
		return (abs(a_col - m_column) <= 1) && (abs(a_row - m_row) <= 1);
	}

	Piece* King::clone() const
	{
		return new King(*this);
	}
}

