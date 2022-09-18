#pragma once
#include "Piece.h"
class Queen : private Piece {
public:
	const static int value = 9;
	static bool isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]);
};