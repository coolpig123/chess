#pragma once
#include <utility>
class Piece {
public:
	int value;
	bool isMoveValid(bool color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]);
};