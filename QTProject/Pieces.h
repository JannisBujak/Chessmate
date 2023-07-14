
#pragma once 

#include <iostream>
#include <vector>
#include <qwidget.h>
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
	int x, y;
public:
	Piece(int x, int y);

	bool same_pos(int x, int y)
	{
		return this->x == x && this->y == y;
	}

	bool same_diagonale(int x, int y)
	{		
		if (same_pos(x, y))
			return false;
		return abs(this->x - x) && abs(this->y - y); 
	}

	bool same_row_or_column(int x, int y)
	{
		return !same_pos(x, y) && (this->x == x || this->y == y);
	}

	virtual QPixmap* get_pxmap(Color color) = 0;
	// virtual bool move_valid(int x, int y, const ChessGame& a_game) = 0;
};

struct Pawn : public Piece
{
	Pawn(int x, int y);

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};

// Turm 
struct Rook : public Piece
{
	Rook(int x, int y)
		: Piece(x, y)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};

struct Knight : public Piece
{
	Knight(int x, int y)
		: Piece(x, y)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};

struct Bishop : public Piece
{
	Bishop(int x, int y)
		: Piece(x, y)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};

struct Queen : public Piece
{
	Queen(int x, int y)
		: Piece(x, y)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};

struct King : public Piece
{
	King(int x, int y)
		: Piece(x, y)
	{}

	virtual QPixmap* get_pxmap(Color color) override;
	bool move_valid(int x, int y, const ChessGame& a_game);
};


