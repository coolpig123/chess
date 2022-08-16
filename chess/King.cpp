#include "King.h"
#include "utilities.h"
#include <iostream>
bool King::isMoveValid(int color, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char board[8][8], bool castlingRights[4]) {
	bool isHorizontal = pieceLastPos.first == pieceNewPos.first && abs(pieceLastPos.second - pieceNewPos.second) == 1;
	bool isVertical = pieceLastPos.second == pieceNewPos.second && abs(pieceLastPos.first - pieceNewPos.first) == 1;
	bool isDiagonal = abs(pieceLastPos.second - pieceNewPos.second) == 1 && abs(pieceLastPos.first - pieceNewPos.first) == 1;
	if ((isHorizontal || isVertical || isDiagonal) && !isUpperCase(board[pieceNewPos.first][pieceNewPos.second]) && color == 1) {
		return true;
	}
	if ((isHorizontal || isVertical || isDiagonal) && !isLowerCase(board[pieceNewPos.first][pieceNewPos.second]) && color == 0) {
		return true;
	}
	char boardAfter[4][8][8];
	for (int i = 0; i < 4; i++) {
		copyBoard(boardAfter[i], board);
	}
	if (color == 1) {
		// king side castle 
		boardAfter[0][7][5] = 'K';
		boardAfter[0][7][4] = ' ';
		if (castlingRights[0] && pieceLastPos.second + 2 == pieceNewPos.second && pieceLastPos.first == pieceNewPos.first && board[7][6] == ' ' && board[7][5] == ' ' && !isKChecked(boardAfter[0], castlingRights)) {
			return true;
		}
		// queen side castle
		boardAfter[1][7][3] = 'K';
		boardAfter[1][7][4] = ' ';
		if (castlingRights[1] && pieceLastPos.second - 2 == pieceNewPos.second && pieceLastPos.first == pieceNewPos.first && board[7][1] == ' ' && board[7][2] == ' ' && board[7][3] == ' ' && !isKChecked(boardAfter[1], castlingRights)) {
			return true;
		}
	}
	else if (color == 0) {
		// king side castle
		boardAfter[0][0][5] = 'K';
		boardAfter[0][0][4] = ' ';
		if (castlingRights[2] && pieceLastPos.second + 2 == pieceNewPos.second && pieceLastPos.first == pieceNewPos.first && board[0][6] == ' ' && board[0][5] == ' ') {
			return true;
		}
		// queen side castle
		boardAfter[1][0][3] = 'K';
		boardAfter[1][0][4] = ' ';
		if (castlingRights[3] && pieceLastPos.second - 2 == pieceNewPos.second && pieceLastPos.first == pieceNewPos.first && board[0][1] == ' ' && board[0][2] == ' ' && board[7][3] == ' ') {
			return true;
		}
	}
	return false;
}
