#include "Pieces.h"


std::vector<QPixmap> Piece::glob_ChessPiecesBitmap;

Piece::Piece(int x, int y)
	: x(x), y(y)
{
}

Pawn::Pawn(int x, int y)
	:Piece(x, y)
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
}


bool Pawn::move_valid(int x, int y, const ChessGame& a_game)
{
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
}
