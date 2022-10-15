#pragma once
#include "raylib.h"
#include "string"

// a function to render the board
void renderBoard(int x,int y,int cellLength);

// a function to render each piece
void renderPiece(int x,int y,int cellLength,char type, Texture2D* pieces, char board[8][8],int boardX,int boardY, bool castlingRights[4],std::pair<int,int> lastMove[2]);

// a function to render the yellow lined squere which indicates where the mouse is
void renderMousePosition(int cellLength, int boardX, int boardY);

// a function to render the piece that the mouse is currently dragging
void renderPieceOnMouse(int cellLength, char piece, Texture2D* pieces);

// a function to render the possible moves a piece can play
void renderPossibleMoves(std::pair<int,int> position,char piece,char board[8][8], int cellLength, int boardX, int boardY,char pieceOnMouse, bool castlingRights[4],std::pair<int,int> lastMove[2]);

// render border of board
void renderBorder(int cellLength, int boardX, int boardY, Font* font);

// render last position of the piece on the mouse
void renderPieceLastPos(int x, int y, int cellLength, char type, Texture2D* pieces, char board[8][8], int boardX, int boardY);

// render pawn promotion options
void renderPromotion(int boardX,int boardY,int cellLength,Texture2D* pieces,int x,char piece);