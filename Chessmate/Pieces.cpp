#include "Pieces.h"

std::vector<QPixmap> Piece::glob_ChessPiecesBitmap;

Piece::Piece(int a_col, int a_row)
	: m_col(a_col), m_row(a_row)
{
}

Pawn::Pawn(int a_col, int a_row)
	:Piece(a_col, a_row)
{
}

QPixmap* Pawn::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[5];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[11];
	};	
	return nullptr;
}


bool Pawn::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	// this->same_pos(a_col, a_row+1);
	// if(a_game.find_piece_in(a_col, a_row+1);
	return true;
}

QPixmap* Rook::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[2];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[8];
	};
	return nullptr;
}

bool Rook::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	return false;
}

QPixmap* Knight::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[4];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[10];
	};
	return nullptr;
}

bool Knight::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	return false;
}

QPixmap* Bishop::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[3];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[9];
	};
	return nullptr;
}

bool Bishop::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	return false;
}

QPixmap* Queen::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[1];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[7];
	};
	return nullptr;
}

bool Queen::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	return false;
}

QPixmap* King::get_pxmap(Color color)
{
	switch (color)
	{
	case  Color::White:
		return &glob_ChessPiecesBitmap[0];
	case  Color::Black:
		return &glob_ChessPiecesBitmap[6];
	};
	return nullptr;
}

bool King::move_valid(int a_col, int a_row, const ChessGame& a_game)
{
	return false;
}
