
#pragma once 

#include <iostream>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QDebug>

class ChessGame;

namespace Pieces
{
    enum class Color
    {
        White,
        Black
    };

	struct Piece
	{
	public:
		static std::vector<QPixmap> glob_ChessPiecesBitmap;

	protected:
		int m_column, m_row;
		Color m_color;
	protected:
		Piece(const Piece& other);
		Piece(int a_col, int a_row, Color a_color);

	public:
		virtual QPixmap& get_pxmap() = 0;

	protected:
		virtual bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const = 0;

	public:
		Color getColor();

		bool same_pos(int a_col, int a_row);

		bool same_diagonale(int a_col, int a_row) const;
		bool same_row_or_column(int a_col, int a_row) const;

		bool pieces_blocking(int a_col, int a_row, const ChessGame& a_board) const;
		bool abandons_king(int a_col, int a_row, ChessGame& a_board) const;

		void updatePosition(int a_col, int a_row);
		bool move_valid(int a_col, int a_row, ChessGame& a_board);

		QPoint getBoardPos() const;

		virtual Piece* clone() const = 0;
	};

	struct Pawn : public Piece
	{
		int m_origRow;
		Pawn(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};

	// Turm 
	struct Rook : public Piece
	{
		Rook(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};

	struct Knight : public Piece
	{
		Knight(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};

	struct Bishop : public Piece
	{
		Bishop(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};

	struct Queen : public Piece
	{
		Queen(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};

	struct King : public Piece
	{
		King(int a_col, int a_row, Color a_color);

		virtual QPixmap& get_pxmap() override;
		bool piece_moveable(int a_col, int a_row, const ChessGame& a_board) const override;

		virtual Piece* clone() const;
	};
}

