#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "utilities.h"
bool Queen::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	bool diagonalValidWhite = Bishop::isMoveValid(1,pieceLastPos,pieceNewPos,board); // is diagonal move valid when white
	bool lineValidWhite = Rook::isMoveValid(1,pieceLastPos,pieceNewPos,board); // is line move valid when white
	bool diagonalValidBlack = Bishop::isMoveValid(0, pieceLastPos, pieceNewPos, board); // is diagonal move valid when black
	bool lineValidBlack = Rook::isMoveValid(0, pieceLastPos, pieceNewPos, board); // is line move valid when black
	if (color == 1 && (diagonalValidWhite || lineValidWhite) && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second])) {
		return true;
	}
	else if (color == 0 && (diagonalValidBlack || lineValidBlack) && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second])) {
		return true;
	}
	else {
		return false;
	}
}