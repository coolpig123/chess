#include "Knight.h"
#include "utilities.h"
bool Knight::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	bool isValidOne = abs(pieceLastPos.second - pieceNewPos.second) == 2 && abs(pieceLastPos.first - pieceNewPos.first) == 1; // is move L shape
	bool isValidTwo = abs(pieceLastPos.first - pieceNewPos.first) == 2 && abs(pieceLastPos.second - pieceNewPos.second) == 1; // is move L rotated shape
	if ((isValidOne || isValidTwo) && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second]) && color == 1) return true;
	if ((isValidOne || isValidTwo) && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second]) && color == 0) return true;
	return false;
}