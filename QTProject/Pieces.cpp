#include "Pieces.h"

Piece::Piece(int x, int y)
	: x(x), y(y)
{
}

Pawn::Pawn(int x, int y)
	:Piece(x, y)
{
}

wchar_t Pawn::get_char(Color color)
{
	switch (color) 
	{
	case Color::White:
		return L'\u2659';
	case Color::Black:
		return L'\u265F';
	}
	
}

bool Pawn::move_valid(int x, int y, const ChessGame& a_game)
{
	return true;
}
