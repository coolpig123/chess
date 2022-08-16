#pragma once
#include "Piece.h"
class Rook : private Piece {
public:
	const static int value = 5;
	static bool isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]);
};