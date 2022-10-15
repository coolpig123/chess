#include "Pawn.h"
#include "utilities.h"
bool Pawn::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8], std::pair<int,int> lastMove[2]) {
	bool isDeltaXZero = pieceLastPos.second == pieceNewPos.second; // check if there is no change in the x axis

	bool isValidOneFileWhite =  isDeltaXZero && pieceLastPos.first - pieceNewPos.first == 1; // check if one file move is valid for white
	bool isValidTwoFileWhite =  isDeltaXZero && pieceLastPos.first - pieceNewPos.first == 2 && pieceLastPos.first == 6 && board[pieceNewPos.first + 1][pieceNewPos.second] == ' '; // check if two file move is valid for white

	bool isValidOneFileBlack = isDeltaXZero && pieceLastPos.first - pieceNewPos.first == -1; // check if one file move is valid for black
	bool isValidTwoFileBlack = isDeltaXZero && pieceLastPos.first - pieceNewPos.first == -2 && pieceLastPos.first == 1 && board[pieceNewPos.first - 1][pieceNewPos.second] == ' '; // check if two file move is valid for black
	 
	bool isValidDiagonalWhite = pieceLastPos.first - pieceNewPos.first == 1 && abs(pieceNewPos.second - pieceLastPos.second) == 1; // check ifF a diagonal capture is valid for white
	bool isValidDiagonalBlack = pieceLastPos.first - pieceNewPos.first == -1 && abs(pieceNewPos.second - pieceLastPos.second) == 1; // check if a diagonal capture is valid for black

	int lastMoveYDiff = abs(lastMove[0].first - lastMove[1].first);
	int deltaX = abs(pieceNewPos.second - pieceLastPos.second);

	bool isLastXNewX = pieceNewPos.second == lastMove[1].second;
	bool isLastYNewY = pieceLastPos.first == lastMove[1].first;

	bool isLastMovep = board[lastMove[1].first][lastMove[1].second] == 'p';
	bool isLastMoveP = board[lastMove[1].first][lastMove[1].second] == 'P';

	bool isNewPosEmpty = board[pieceNewPos.first][pieceNewPos.second] == ' ';
	bool isNewPosOccupied = board[pieceNewPos.first][pieceNewPos.second] != ' ';

	if (color == 1) { // if the color is white
		if (isValidOneFileWhite && isNewPosEmpty) return true;
		if (isValidTwoFileWhite && isNewPosEmpty) return true;
		if (isValidDiagonalWhite && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second]) && isNewPosOccupied) return true;
		if (lastMoveYDiff == 2 && isLastMovep && deltaX == 1 && pieceNewPos.first + 1 == lastMove[1].first && isLastXNewX && isLastYNewY) return true;
	}
	else if (color == 0) { // if the color is black
		if (isValidOneFileBlack && isNewPosEmpty) return true;
		if (isValidTwoFileBlack && isNewPosEmpty) return true;
		if (isValidDiagonalBlack && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second]) && isNewPosOccupied) return true;
		if (lastMoveYDiff == 2 && isLastMoveP && deltaX == 1 && pieceNewPos.first - 1 == lastMove[1].first && isLastXNewX && isLastYNewY) return true;
	}
	return false;
}