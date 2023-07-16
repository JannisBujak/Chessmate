#include "Pieces.h"

std::vector<QPixmap> Piece::glob_ChessPiecesBitmap;

Piece::Piece(int a_col, int a_row, Color a_color)
	: m_col(a_col)
	, m_row(a_row)
	, m_color(a_color)
{}

Pawn::Pawn(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& Pawn::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[5];
	case  Color::Black:
	default:
		return glob_ChessPiecesBitmap[11];
	};	
}


bool Pawn::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	// this->same_pos(a_col, a_row+1);
	// if(a_game.find_piece_in(a_col, a_row+1);
	return true;
}

Rook::Rook(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& Rook::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[2];
	case  Color::Black:
	default:
		return glob_ChessPiecesBitmap[8];
	};
}

bool Rook::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	return false;
}

Knight::Knight(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& Knight::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[4];
	case  Color::Black:
	default:
		return glob_ChessPiecesBitmap[10];
	};
}

bool Knight::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	return false;
}

Bishop::Bishop(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& Bishop::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[3];
	case  Color::Black:
		return glob_ChessPiecesBitmap[9];
	};
}

bool Bishop::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	return false;
}

Queen::Queen(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& Queen::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[1];
	case  Color::Black:
		return glob_ChessPiecesBitmap[7];
	};
}

bool Queen::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	return false;
}

King::King(int a_col, int a_row, Color a_color)
	: Piece(a_col, a_row, a_color)
{
}

QPixmap& King::get_pxmap()
{
	switch (m_color)
	{
	case  Color::White:
		return glob_ChessPiecesBitmap[0];
	case  Color::Black:
		return glob_ChessPiecesBitmap[6];
	};
}

bool King::move_valid(int a_col, int a_row, const Chessboard& a_board)
{
	return false;
}
