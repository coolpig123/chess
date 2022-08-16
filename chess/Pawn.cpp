#include "Pawn.h"
#include "utilities.h"
bool Pawn::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8]) {
	bool isDeltaXZero = pieceLastPos.second == pieceNewPos.second; // check if there is no change in the x axis

	bool isValidOneFileWhite =  isDeltaXZero && pieceLastPos.first - pieceNewPos.first == 1; // check if one file move is valid for white
	bool isValidTwoFileWhite =  isDeltaXZero && pieceLastPos.first - pieceNewPos.first == 2 && pieceLastPos.first == 6 && board[pieceNewPos.first + 1][pieceNewPos.second] == ' '; // check if two file move is valid for white

	bool isValidOneFileBlack = isDeltaXZero && pieceLastPos.first - pieceNewPos.first == -1; // check if one file move is valid for black
	bool isValidTwoFileBlack = isDeltaXZero && pieceLastPos.first - pieceNewPos.first == -2 && pieceLastPos.first == 1 && board[pieceNewPos.first - 1][pieceNewPos.second] == ' '; // check if two file move is valid for black
	 
	bool isValidDiagonalWhite = pieceLastPos.first - pieceNewPos.first == 1 && abs(pieceNewPos.second - pieceLastPos.second) == 1; // check if a diagonal capture is valid for white
	bool isValidDiagonalBlack = pieceLastPos.first - pieceNewPos.first == -1 && abs(pieceNewPos.second - pieceLastPos.second) == 1; // check if a diagonal capture is valid for black

	if (color == 1) { // if the color is white
		if (isValidOneFileWhite && board[pieceNewPos.first][pieceNewPos.second] == ' ') return true;
		if (isValidTwoFileWhite && board[pieceNewPos.first][pieceNewPos.second] == ' ') return true;
		if (isValidDiagonalWhite && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second]) && board[pieceNewPos.first][pieceNewPos.second] != ' ') return true;
	}
	else if (color == 0) { // if the color is black
		if (isValidOneFileBlack && board[pieceNewPos.first][pieceNewPos.second] == ' ') return true;
		if (isValidTwoFileBlack && board[pieceNewPos.first][pieceNewPos.second] == ' ') return true;
		if (isValidDiagonalBlack && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second]) && board[pieceNewPos.first][pieceNewPos.second] != ' ') return true;
	}
	return false;
}