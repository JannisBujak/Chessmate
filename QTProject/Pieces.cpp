#include "Pieces.h"

Piece::Piece(int x, int y)
	: x(x), y(y)
{
}

Pawn::Pawn(int x, int y)
	:Piece(x, y)
{
}

std::wstring Pawn::get_char()
{
	std::wcout << '\u2659';
	std::wcout << "\u2659";
	return std::wstring();
	// return std::wstring(L"\u2659");
}

bool Pawn::move_valid(int x, int y, const ChessGame& a_game)
{
	return true;
}
