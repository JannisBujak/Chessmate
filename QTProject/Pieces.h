
#ifndef PIECES_H
#define PIECES_H

#include <iostream>

class ChessGame;

enum class Color
{
	White,
	Black
};

struct Piece
{
public:

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

	virtual std::wstring get_char() = 0;
	virtual bool move_valid(int x, int y, const ChessGame& a_game) = 0;
};

struct King : public Piece
{};

// Turm 
struct Rook : public Piece
{};

struct Bishop : public Piece
{};

struct Queen : public Piece
{};

struct Knight : public Piece
{};

struct Pawn : public Piece
{
	Pawn(int x, int y);

	virtual std::wstring get_char() override;
	virtual bool move_valid(int x, int y, const ChessGame& a_game) override;
};



#endif