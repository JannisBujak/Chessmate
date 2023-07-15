
#pragma once 

#include <iostream>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QDebug>

class ChessGame;

enum class Color
{
	White,
	Black
};

struct Piece
{
public:
	static std::vector<QPixmap> glob_ChessPiecesBitmap;

private:
	int m_col, m_row;
public:
	Piece(int a_col, int a_row);

	bool same_pos(int a_col, int a_row)
	{
		return this->m_col == a_col && this->m_row == a_row;
	}

	bool same_diagonale(int a_col, int a_row)
	{		
		if (same_pos(a_col, a_row))
			return false;
		return abs(this->m_col - a_col) && abs(this->m_row - a_col); 
	}

	bool same_row_or_column(int a_col, int a_row)
	{
		return !same_pos(a_row, a_col) && (this->m_col == a_col || this->m_row == a_row);
	}

	virtual QPixmap* get_pxmap(Color color) = 0;
	// virtual bool move_valid(int m_col, int m_row, const ChessGame& a_game) = 0;
};

struct Pawn : public Piece
{
	Pawn(int a_col, int a_row);

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};

// Turm 
struct Rook : public Piece
{
	Rook(int a_col, int a_row)
		: Piece(a_col, a_row)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};

struct Knight : public Piece
{
	Knight(int a_col, int a_row)
		: Piece(a_col, a_row)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};

struct Bishop : public Piece
{
	Bishop(int a_col, int a_row)
		: Piece(a_col, a_row)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};

struct Queen : public Piece
{
	Queen(int a_col, int a_row)
		: Piece(a_col, a_row)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};

struct King : public Piece
{
	King(int a_col, int a_row)
		: Piece(a_col, a_row)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int a_col, int a_row, const ChessGame& a_game);
};


