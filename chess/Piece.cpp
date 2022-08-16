#include "Piece.h"
#include "utilities.h"
bool isMoveValid(bool color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	if ((color && isUpperCase(board[pieceNewPos.first][pieceNewPos.second])) || // if the color is white and the new position contains a white piece
		(!color && isLowerCase(board[pieceNewPos.first][pieceNewPos.second]))) { // if the color is black and the new position contains a black piece
		return false;
	}
	return true;
}
