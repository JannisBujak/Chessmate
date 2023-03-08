#include "Chessboard.h"

void Chessboard::print(const ChessGame& a_game)
{
	using namespace std;
	wcout << "\t|";
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		wcout << "  " << (char)('a' + x) << "   |";
	}
	wcout << endl;
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		wcout << (y + 1) << "\t|";
		for (int x = 0; x < BOARD_WIDTH; ++x) 
		{
			std::wcout << "  ";
			auto [piece, color] = a_game.piece_at(x, y);
			if (piece) {
				std::wcout << (color == Color::White ? 'w' : 'b');
				std::wcout << piece->get_char();
			}
			else
				wcout << "  "; 
			
			std::wcout << "  |";
		}
		wcout << endl;
	}
}
