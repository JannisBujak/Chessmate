#include "ChessGame.h"

ChessGame::ChessGame()
{
	init();
}

void ChessGame::init()
{

	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		white.push_back(std::make_unique<Pawn>(x, 1));
		black.push_back(std::make_unique<Pawn>(x, 6));
	}

	// R K B Q K B K R

}

Piece* ChessGame::find_piece_in(int x, int y, const std::vector<std::unique_ptr<Piece>>& a_list)
{
	for (int i = 0; i < a_list.size(); ++i)
	{
		if (a_list[i]->same_pos(x, y))
		{
			return a_list[i].get();
		}
	}
	return nullptr;
}

std::pair<Piece*, Color> ChessGame::piece_at(int x, int y) const
{
	using ColPiecePtr = std::pair<Piece*, Color>;
	Piece* piece_at;
	if (piece_at = find_piece_in(x, y, white))
		return ColPiecePtr(piece_at, Color::White);
	if (piece_at = find_piece_in(x, y, black))
		return ColPiecePtr(piece_at, Color::White);
	return ColPiecePtr(nullptr, Color::White);
}


