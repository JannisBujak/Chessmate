#include "ChessGame.h"

ChessGame::ChessGame()
{
	init();
}

void ChessGame::init()
{

	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		white.push_back(std::make_unique<Pawn>(x, 6));
		black.push_back(std::make_unique<Pawn>(x, 1));
	}

	auto fill_backrow = [](std::vector<std::unique_ptr<Piece>>&a_team, int col)
	{
		a_team.push_back(std::make_unique<Rook>(0, col));
		a_team.push_back(std::make_unique<Knight>(1, col));
		a_team.push_back(std::make_unique<Bishop>(2, col));
		a_team.push_back(std::make_unique<Queen>(3, col));
		a_team.push_back(std::make_unique<King>(4, col));
		a_team.push_back(std::make_unique<Bishop>(5, col));
		a_team.push_back(std::make_unique<Knight>(6, col));
		a_team.push_back(std::make_unique<Rook>(7, col));
	};
	fill_backrow(black, 0);
	fill_backrow(white, 7);

	

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
		return ColPiecePtr(piece_at, Color::Black);
	return ColPiecePtr(nullptr, Color::White);
}


