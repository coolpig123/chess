#pragma once
#include "utility"
#include <vector>
#include "string"

// function to get the mouse position on the board
std::pair<int, int> getMousePosition(int cellLength, int boardX, int boardY);

// function handle when user try's to move a piece
void movePieceToMouse(int cellLength, char* pieceOnMouse, char board[8][8], std::pair<int, int>* pieceLastPos,bool* turn,int boardX,int boardY,bool castlingRights[4]);

// function to return if the position of the mouse is valid or invalid
bool isMousePositionValid(int screenWidth, int screenHeight,char *pieceOnMouse);

// function to print the board to the console 
void printBoard(char board[8][8]);

// check if the move is valid
bool isMoveValid(char piece, std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char lastBoard[8][8], bool castlingRights[4]);

// check if a letter is upper case
bool isUpperCase(char letter);

// check if a letter is lower case
bool isLowerCase(char letter);

// check if a row is empty
bool isRowEmpty(int start, int end,int row, char board[8][8]);

// check if a column is empty
bool isColumnEmpty(int start, int end,int column, char board[8][8]);

// check if a diagonal is empty
bool isDiagonalEmpty(std::pair<int, int> pieceLastPos, std::pair<int, int> pieceNewPos, char lastBoard[8][8]);

// check if the white king is being checked
bool isKChecked(char board[8][8],bool castlingRights[4]);

// check if the black king is being checked (with giving the checking piece)
bool isKChecked(char board[8][8],std::pair<int,int>* checkingPiece, bool castlingRights[4]);

// check if the black king is being checked
bool iskChecked(char board[8][8], bool castlingRights[4]);

// check if the black king is being checked (with giving the checking piece)
bool iskChecked(char board[8][8], std::pair<int, int>* checkingPiece, bool castlingRights[4]);

// check if side is checked
bool isSideChecked(char movedPiece, char board[8][8],bool castlingRights[4]);

// check if black is mated
bool isBlackMated(char board[8][8], bool castlingRights[4]);

// check if white is mated
bool isWhiteMated(char board[8][8], bool castlingRights[4]);

// read FEN notation and return a board containing the FEN
void readFEN(std::string FEN, char board[8][8],bool* turn,bool castlingRights[4]);

// split string using a given delimiter
std::vector<std::string> split(std::string text, char delimiter);

// check if a character is a number
bool isNumber(char character);

// is there a draw by insufficent material
bool isDrawByMaterial(char board[8][8]);

// is there a draw by stalemate
bool isDrawByStaleMate(char board[8][8]);

// copy board to another board
void copyBoard(char copyToboard[8][8], char copiedBoard[8][8]);