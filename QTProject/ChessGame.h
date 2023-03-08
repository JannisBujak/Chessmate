
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8


#include <vector>
#include <iostream>

#include "Pieces.h"

class ChessGame
{
private:
	std::vector<std::unique_ptr<Piece>> white, black;
public:
	ChessGame();

	void init();

	static Piece* find_piece_in(int x, int y, const std::vector<std::unique_ptr<Piece>>& a_list);

	std::pair< Piece*, Color> piece_at(int x, int y) const;

	bool checkmate() const;
};

#endif 