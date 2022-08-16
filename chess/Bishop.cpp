#include "Bishop.h"
#include "utilities.h"
bool Bishop::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	bool deltaEqual = abs(pieceLastPos.second - pieceNewPos.second) == abs(pieceLastPos.first - pieceNewPos.first); // check if the delta of x and y are equal
	bool diagonalEmpty = isDiagonalEmpty(pieceLastPos, pieceNewPos, board); // check if a diagonal is empty
	// if color is white
	if (color == 1) { 
		if (deltaEqual && diagonalEmpty && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second])) return true;
	}
	// if color is black
	else if (color == 0) {
		if (deltaEqual && diagonalEmpty && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second])) return true;
	}
	return false;
}