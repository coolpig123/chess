#pragma once
#include "Piece.h"
class Pawn : private Piece {
public:
	const static int value = 1;
	static bool isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8],std::pair<int,int> lastMove[2]);
};