#pragma once
#include "Piece.h"
class King : private Piece {
public:
	const static int value = 0;
	static bool isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8],bool castlingRights[4]);
};