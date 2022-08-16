#include "Rook.h"
#include "utilities.h"
bool Rook::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	bool rowMoveValid = (pieceLastPos.first == pieceNewPos.first && isRowEmpty(pieceLastPos.second, pieceNewPos.second, pieceLastPos.first, board)); // check if row move is valid
	bool columnMoveValid = (pieceLastPos.second == pieceNewPos.second && isColumnEmpty(pieceLastPos.first, pieceNewPos.first, pieceLastPos.second, board)); // check if column move is valid
	if (color == 1) {
		if ((columnMoveValid || rowMoveValid) && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second])) return true;
	}
	else if (color == 0) {
		if ((columnMoveValid || rowMoveValid) && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second])) return true;
	}
	return false;
}