#include "utilities.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
#include "raylib.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
std::pair<int, int> getMousePosition(int cellLength,int boardX,int boardY) {
	std::pair<int, int> position;
	if (GetMouseX() <= GetScreenWidth() && GetMouseX() >= boardX && GetMouseY() <= GetScreenHeight() && GetMouseY() >= boardY) {
		for (int i = boardX; i < cellLength * 8 + boardX; i += cellLength) {
			if (GetMouseX() >= i  && GetMouseX() <= i + cellLength) {
				position.first = i / cellLength;
				break;
			}
		}
		for (int i = boardY; i < cellLength * 8 + boardY; i += cellLength) {
			if (GetMouseY() >= i && GetMouseY() <= i + cellLength) {
				position.second = i / cellLength;
				break;
			}
		}
	}
	else {
		position.first = -1;
		position.second = -1;
	}
	return position;
}
int movePieceToMouse(int cellLength, char* pieceOnMouse, char board[8][8], std::pair<int, int>* pieceLastPos, bool* turn,int boardX,int boardY, bool castlingRights[4], Sound fxMove, Sound fxCapture) {
	// check if there is a piece on the mouse
	bool isPieceOnMouse = (*pieceOnMouse != ' '); 
	
	// coordinates of the mouse on the board
	int mousePosX = getMousePosition(cellLength, boardX, boardY).first;
	int mousePosY = getMousePosition(cellLength, boardX, boardY).second;
	int promotionFile = -1;

	// common conditions to clean up the code
	bool isMoveVal = isMoveValid(*pieceOnMouse, *pieceLastPos, std::make_pair(mousePosY, mousePosX), board,castlingRights);
	bool isLastPosMousePos = pieceLastPos->first != mousePosY || pieceLastPos->second != mousePosX;
	bool isMousePosValid = isMousePositionValid(GetScreenWidth(), GetScreenHeight(), pieceOnMouse);
	bool isTurnValid = (isLowerCase(*pieceOnMouse) && !*turn) || (isUpperCase(*pieceOnMouse) && *turn);

	// check if the left button is up
	bool isLeftUp = IsMouseButtonUp(MOUSE_BUTTON_LEFT);

	// char variables
	char cellOnMouse = board[mousePosY][mousePosX];
	char boardAfter[8][8];

	// make a board after a certain move
	copyBoard(boardAfter, board);
	boardAfter[mousePosY][mousePosX] = *pieceOnMouse;

	// check if someone is checked
	bool isChecked = isSideChecked(*pieceOnMouse, boardAfter, castlingRights);

	// this if statement is for loading a piece to the mouse
	if (!isPieceOnMouse && cellOnMouse != ' ' && 
		IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
		((*turn && isUpperCase(cellOnMouse) ) || 
	     (!*turn && isLowerCase(cellOnMouse)))) {

		*pieceOnMouse = cellOnMouse;

		board[mousePosY][mousePosX] = ' ';

		*pieceLastPos = std::make_pair(mousePosY, mousePosX);
	}
	// this if statement is for unloading a piece from the mouse
	else if (isPieceOnMouse && 
			 IsMouseButtonUp(MOUSE_BUTTON_LEFT) && 
			 isMousePosValid && isMoveVal && 
			 (!isChecked || (mousePosY == pieceLastPos->first && mousePosX == pieceLastPos->second)) &&
		     isTurnValid) {

		if (mousePosY == 0 && *pieceOnMouse == 'P')  promotionFile = mousePosX;
		if (mousePosY == 7 && *pieceOnMouse == 'p')  promotionFile = mousePosX;

		playSoundMove(isLastPosMousePos, boardAfter, pieceLastPos, board, pieceOnMouse, fxMove, fxCapture);

		handleCastling(pieceOnMouse, pieceLastPos, mousePosX, castlingRights, board);

		board[mousePosY][mousePosX] = *pieceOnMouse;

		*pieceOnMouse = ' ';
		if (mousePosY != pieceLastPos->first || mousePosX != pieceLastPos->second) *turn = !(*turn);
	}
	// put the piece back to it's place if it's out of screen boundries
	else if (isPieceOnMouse && isLeftUp && !isMousePosValid) {
		board[(*pieceLastPos).first][(*pieceLastPos).second] = *pieceOnMouse;

		*pieceOnMouse = ' ';
	}
	// put the piece back to it's place if it's not valid
	else if (isPieceOnMouse && isLeftUp && isMousePosValid && (!isMoveVal || isChecked)) {
		board[(*pieceLastPos).first][(*pieceLastPos).second] = *pieceOnMouse;

		*pieceOnMouse = ' ';
	}
	// put the piece back to it's place if it's not the side's turn
	else if (isPieceOnMouse && isLeftUp && !isTurnValid) {
		board[(*pieceLastPos).first][(*pieceLastPos).second] = *pieceOnMouse;

		*pieceOnMouse = ' ';
	}
	return promotionFile;

}
bool isMousePositionValid(int screenWidth, int screenHeight, char* pieceOnMouse) {
	if (*pieceOnMouse != ' ') {
		if (GetMouseX() < 0) {
			return false;
		}
		else if (GetMouseX() > screenWidth) {
			return false;
		}
		else if (GetMouseY() < 0) {
			return false;
		}
		else if (GetMouseY() > screenHeight) {
			return false;
		}
	}
	return true;
}
void printBoard(char board[8][8]) {
	for (int i = 0; i < 8; i++) {
		std::cout << "|";
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << "|";
		}
		std::cout << std::endl;
		std::cout << "-----------------" << std::endl;
	}
}
bool isMoveValid(char piece, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char lastBoard[8][8], bool castlingRights[4]) {
	std::map<char, bool> isValid = { {'P',Pawn::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard)},
									 {'p',Pawn::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard)},
									 {'R',Rook::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard)},
									 {'r',Rook::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard)},
									 {'B',Bishop::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard)},
									 {'b',Bishop::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard)},
									 {'Q',Queen::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard)},
									 {'q',Queen::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard)},
									 {'K',King::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard,castlingRights)},
									 {'k',King::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard,castlingRights)},
									 {'N',Knight::isMoveValid(1, pieceLastPos, pieceNewPos, lastBoard)},
									 {'n',Knight::isMoveValid(0, pieceLastPos, pieceNewPos, lastBoard)},
	};
	return isValid[piece];
}
bool isUpperCase(char letter) {
	if (letter == 'P' || letter == 'R' || letter == 'N' || letter == 'B' || letter == 'Q' || letter == 'K') {
		return true;
	}
	else {
		return false;
	}
}
bool isLowerCase(char letter) {
	if (letter == 'p' || letter == 'r' || letter == 'n' || letter == 'b' || letter == 'q' || letter == 'k') {
		return true;
	}
	else {
		return false;
	}
}
bool isRowEmpty(int start, int end, int row, char board[8][8]) {
	for (int i = std::min(start, end) + 1; i <= std::max(start, end) - 1; i++) {
		if (board[row][i] != ' ') {
			return false;
		}
	}
	return true;
}
bool isColumnEmpty(int start, int end, int column, char board[8][8]) {
	for (int i = std::min(start, end) + 1; i <= std::max(start, end) - 1; i++) {
		if (board[i][column] != ' ') {
			return false;
		}
	}
	return true;
}
bool isDiagonalEmpty(std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char lastBoard[8][8]) {
	int j;
	if (pieceLastPos.first < pieceNewPos.first && pieceLastPos.second < pieceNewPos.second) {
		j = pieceLastPos.second + 1;
		for (int i = pieceLastPos.first + 1; i < pieceNewPos.first; i++) {
			if (lastBoard[i][j] != ' ') {
				return false;
			}
			j++;
		}
	}
	else if (pieceLastPos.first < pieceNewPos.first && pieceLastPos.second > pieceNewPos.second) {
		j = pieceLastPos.second - 1;
		for (int i = pieceLastPos.first + 1; i < pieceNewPos.first; i++) {
			if (lastBoard[i][j] != ' ') {
				return false;
			}
			j--;
		}
	}
	else if (pieceLastPos.first > pieceNewPos.first && pieceLastPos.second > pieceNewPos.second) {
		j = pieceLastPos.second - 1;
		for (int i = pieceLastPos.first - 1; i > pieceNewPos.first; i--) {
			if (lastBoard[i][j] != ' ') {
				return false;
			}
			j--;
		}
	}
	else if (pieceLastPos.first > pieceNewPos.first && pieceLastPos.second < pieceNewPos.second) {
		j = pieceLastPos.second + 1;
		for (int i = pieceLastPos.first - 1; i > pieceNewPos.first; i--) {
			if (lastBoard[i][j] != ' ') {
				return false;
			}
			j++;
		}
	}
	return true;
}
bool isKChecked(char board[8][8],bool castlingRights[4]) {
	std::pair<int, int> kingPos;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 'K') {
				kingPos = std::make_pair(i, j);
				break;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isLowerCase(board[i][j]) && isMoveValid(board[i][j], std::make_pair(i, j), kingPos, board, castlingRights)) {
				return true;
			}
		}
	}
	return false;
}

bool iskChecked(char board[8][8],bool castlingRights[4]) {
	std::pair<int, int> kingPos;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 'k') {
				kingPos = std::make_pair(i, j);
				break;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isUpperCase(board[i][j]) && isMoveValid(board[i][j], std::make_pair(i, j), kingPos, board,castlingRights)) {
				return true;
			}
		}
	}
	return false;
}
bool isSideChecked(char movedPiece, char board[8][8],bool castlingRights[4]) {
	if (isUpperCase(movedPiece)) {
		if (isKChecked(board, castlingRights)) return true;
	}
	else {
		if (iskChecked(board, castlingRights)) return true;
	}
	return false;
}
bool isKChecked(char board[8][8], std::pair<int, int>* checkingPiece, bool castlingRights[4]) {
	std::pair<int, int> kingPos;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 'K') {
				kingPos = std::make_pair(i, j);
				break;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isLowerCase(board[i][j]) && isMoveValid(board[i][j], std::make_pair(i, j), kingPos, board,castlingRights)) {
				checkingPiece->first = i;
				checkingPiece->second = j;
				return true;
			}
		}
	}
	return false;
}
bool iskChecked(char board[8][8], std::pair<int, int>* checkingPiece, bool castlingRights[4]) {
	std::pair<int, int> kingPos;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 'k') {
				kingPos = std::make_pair(i, j);
				break;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isUpperCase(board[i][j]) && isMoveValid(board[i][j], std::make_pair(i, j), kingPos, board,castlingRights)) {
				checkingPiece->first = i;
				checkingPiece->second = j;
				return true;
			}
		}
	}
	return false;
}
bool isBlackMated(char board[8][8], bool castlingRights[4]) {
	char boardAfter[8][8];
	if (!iskChecked(board,castlingRights)) return false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isLowerCase(board[i][j])) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						copyBoard(boardAfter, board);
						boardAfter[a][b] = board[i][j];
						boardAfter[i][j] = ' ';
						if (isMoveValid(board[i][j], std::make_pair(i, j), std::make_pair(a, b), board,castlingRights) && 
							!iskChecked(boardAfter, castlingRights)) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool isWhiteMated(char board[8][8],bool castlingRights[4]) {
	char boardAfter[8][8];
	if (!isKChecked(board, castlingRights)) return false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isUpperCase(board[i][j])) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						copyBoard(boardAfter, board);
						boardAfter[a][b] = board[i][j];
						boardAfter[i][j] = ' ';
						if (isMoveValid(board[i][j], std::make_pair(i, j), std::make_pair(a, b), board,castlingRights) && 
							!isKChecked(boardAfter, castlingRights)) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void readFEN(std::string FEN, char board[8][8], bool* turn, bool castlingRights[4]) {
	std::vector<std::string> FENSPLITTED = split(FEN, ' ');
	int counter = 0;
	std::vector<std::vector<char>> boardVector = { {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '},
											 {' ',' ',' ',' ',' ',' ',' ',' '} };
	int row = 0;
	int column = 0;
	for (size_t i = 0; i < FENSPLITTED[0].size(); i++) {
		if (isNumber(FENSPLITTED[0][i])) {
			column += int(FENSPLITTED[0][i] - 48);

		}
		else if (FENSPLITTED[0][i] == '/') {
			row++;
			column = 0;

		}
		else {
			boardVector[row][column] = FENSPLITTED[0][i];
			column++;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = boardVector[i][j];
		}
	}

	if (FENSPLITTED[1][0] == 'w') {
		*turn = true;
	}
	else if (FENSPLITTED[1][0] == 'b') {
		*turn = false;
	}
	for (int i = 0; i < 4; i++) {
		castlingRights[i] = false;
	}
	if (FENSPLITTED[2].find("K") != std::string::npos) castlingRights[0] = true;
	if (FENSPLITTED[2].find("Q") != std::string::npos) castlingRights[1] = true;
	if (FENSPLITTED[2].find("k") != std::string::npos) castlingRights[2] = true;
	if (FENSPLITTED[2].find("q") != std::string::npos) castlingRights[3] = true;
}

std::vector<std::string> split(std::string text, char delimiter) {
	std::vector<std::string> splits;
	std::string sample = "";
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == delimiter && sample != "") {
			splits.push_back(sample);
			sample = "";
		}
		else if (text[i] == delimiter && sample == "") {
			continue;
		}
		else {
			sample += text[i];
		}
	}
	if (sample != "") splits.push_back(sample);
	return splits;
}

bool isNumber(char character) {
	if (character == '0' ||
		character == '1' ||
		character == '2' ||
		character == '3' ||
		character == '4' ||
		character == '5' ||
		character == '6' ||
		character == '7' ||
		character == '8' ||
		character == '9') {
		return true;
	}
	return false;
}

bool isDrawByMaterial(char board[8][8]) {
	std::vector<char> pieces;
	int totalValue = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != ' ' && board[i][j] != 'k' && board[i][j] != 'K') {
				if (std::tolower(board[i][j]) == 'q') totalValue += 9;
				if (std::tolower(board[i][j]) == 'r') totalValue += 5;
				if (std::tolower(board[i][j]) == 'n') totalValue += 3;
				if (std::tolower(board[i][j]) == 'b') totalValue += 3;
				if (std::tolower(board[i][j]) == 'p') totalValue += 1;
				pieces.push_back(board[i][j]);
			}
		}
	}

	if (pieces.size() == 0 || (pieces.size() == 1 && totalValue == 3)) return true;
	return false;
}

bool isDrawByStaleMate(char board[8][8]) {
	return true;
}

void copyBoard(char copyToboard[8][8], char copiedBoard[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			copyToboard[i][j] = copiedBoard[i][j];
		}
	}
}

int calcBoardDiff(char boardOne[8][8], char boardTwo[8][8]) {
	int boardOneSum = 0;
	int boardTwoSum = 0;
	std::map<char, int> values = { {'k',0},{'q',9}, {'p',1}, {'r',5}, {'n',3}, {'b',3}, {' ',0} };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			boardOneSum += values[char(std::tolower(boardOne[i][j]))];
			boardTwoSum += values[char(std::tolower(boardTwo[i][j]))];
		}
	}
	return abs(boardOneSum - boardTwoSum);
}

void playSoundMove(bool isLastPosMousePos, char boardAfter[8][8],std::pair<int,int>* pieceLastPos,char board[8][8],char* pieceOnMouse, Sound fxMove, Sound fxCapture) {
	boardAfter[pieceLastPos->first][pieceLastPos->second] = ' ';
	char newBoard[8][8];
	copyBoard(newBoard, board);
	newBoard[pieceLastPos->first][pieceLastPos->second] = *pieceOnMouse;

	// if statement to play a sound if a piece was captured
	if (calcBoardDiff(newBoard, boardAfter) != 0 && isLastPosMousePos) {
		PlaySound(fxCapture);
	}
	// else if statement to play sound if a piece was moved
	else if (isLastPosMousePos) {
		PlaySound(fxMove);
	}
}

void handleCastling(char* pieceOnMouse, std::pair<int, int>* pieceLastPos, int mousePosX, bool castlingRights[4], char board[8][8]) {
	// if white castles king side
	if ((*pieceOnMouse == 'K' && pieceLastPos->second + 2 == mousePosX)) {
		castlingRights[0] = false;
		castlingRights[1] = false;
		board[7][5] = 'R';
		board[7][7] = ' ';
	}
	// else if white castles queen side
	else if ((*pieceOnMouse == 'K' && pieceLastPos->second - 2 == mousePosX)) {
		castlingRights[0] = false;
		castlingRights[1] = false;
		board[7][0] = ' ';
		board[7][3] = 'R';
		// else if black castles king side
	}
	else if ((*pieceOnMouse == 'k' && pieceLastPos->second + 2 == mousePosX)) {
		castlingRights[2] = false;
		castlingRights[3] = false;
		board[0][5] = 'r';
		board[0][7] = ' ';
	}// else if black castles queen side
	else if ((*pieceOnMouse == 'k' && pieceLastPos->second - 2 == mousePosX)) {
		castlingRights[2] = false;
		castlingRights[3] = false;
		board[0][0] = ' ';
		board[0][3] = 'r';
	}
	else if (*pieceOnMouse == 'K') {
		castlingRights[0] = false;
		castlingRights[1] = false;
	}
	else if (*pieceOnMouse == 'k') {
		castlingRights[2] = false;
		castlingRights[3] = false;
	}
}
int handlePromotion(char piece, int x, char board[8][8],int boardX,int boardY,int cellLength) {
	int rank = x;
	int file = -1;

	int mousePosX = getMousePosition(cellLength, boardX, boardY).first;
	int mousePosY = getMousePosition(cellLength, boardX, boardY).second;

	if (isUpperCase(piece)) file = 0;
	else if (isLowerCase(piece)) file = 7;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mousePosX == rank) {
		if (mousePosY == 7 && isLowerCase(piece)) board[file][rank] = 'q';
		if (mousePosY == 6 && isLowerCase(piece)) board[file][rank] = 'r';
		if (mousePosY == 5 && isLowerCase(piece)) board[file][rank] = 'b';
		if (mousePosY == 4 && isLowerCase(piece)) board[file][rank] = 'n';
		if (mousePosY == 3 && isUpperCase(piece)) board[file][rank] = 'N';
		if (mousePosY == 2 && isUpperCase(piece)) board[file][rank] = 'B';
		if (mousePosY == 1 && isUpperCase(piece)) board[file][rank] = 'R';
		if (mousePosY == 0 && isUpperCase(piece)) board[file][rank] = 'Q';
	}
	if (board[file][rank] != 'p' && board[file][rank] != 'P') return -1;

	return x;
}

