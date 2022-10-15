#include "render.h"
#include "raylib.h"
#include "Colors.h"
#include "utilities.h"
#include <iostream>
#include <string>

#define OFFSET1 Vector2{ float(x) * cellLength + 15 + boardX,float(y) * cellLength + 5 + boardY }
#define OFFSET2 Vector2{ float(x) * cellLength + boardX,float(y) * cellLength + 5 + boardY }
#define OFFSET3 Vector2{ float(GetMouseX()) - 35,float(GetMouseY()) - 45 }
#define OFFSET4 Vector2{ float(GetMouseX()) - 50,float(GetMouseY()) - 45 }
#define OFFSET5 Vector2{ float(GetMouseX()) - 40,float(GetMouseY()) - 45 }
#define OFFSET6 Vector2{ float(x) * cellLength + 5 + boardX,float(y) * cellLength + 5 + boardY }

void renderBoard(int x, int y, int cellLength) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
				DrawRectangle(i * cellLength + x, j * cellLength + y, cellLength, cellLength, DARKSQUARE);
			}
			else {
				DrawRectangle(i * cellLength + x, j * cellLength + y, cellLength, cellLength, LIGHTSQUARE );
			}
		}
	}
}

void renderPiece(int x, int y, int cellLength, char type, Texture2D* pieces,char board[8][8],int boardX, int boardY,bool castlingRights[4], std::pair<int,int> lastMove[2]) {
	switch (type) {
	case 'p':
		DrawTextureRec(*pieces, Rectangle{ 460,90,90,90 }, OFFSET1, WHITE);
		break;
	case 'P':
		DrawTextureRec(*pieces, Rectangle{ 460,0,90,90 }, OFFSET1, WHITE);
		break;
	case 'r':
		DrawTextureRec(*pieces, Rectangle{ 370,90,90,90 }, OFFSET1, WHITE);
		break;
	case 'R':
		DrawTextureRec(*pieces, Rectangle{ 370,0,90,90 }, OFFSET1, WHITE);
		break;
	case 'n':
		DrawTextureRec(*pieces, Rectangle{ 280,90,90,90 }, OFFSET1, WHITE);
		break;
	case 'N':
		DrawTextureRec(*pieces, Rectangle{ 280,0,90,90 }, OFFSET1, WHITE);
		break;
	case 'b':
		DrawTextureRec(*pieces, Rectangle{ 190,90,90,90 }, OFFSET1, WHITE);
		break;
	case 'B':
		DrawTextureRec(*pieces, Rectangle{ 190,0,90,90 }, OFFSET1, WHITE);
		break;
	case 'q':
		DrawTextureRec(*pieces, Rectangle{ 85,90,90,90 }, OFFSET2, WHITE);
		break;
	case 'Q':
		DrawTextureRec(*pieces, Rectangle{ 85,0,90,90 }, OFFSET2, WHITE);
		break;
	case 'k':
		if (iskChecked(board, castlingRights,lastMove) && (x + y) % 2 == 0) {
			DrawCircleGradient(x * cellLength + cellLength / 2 + boardX, y * cellLength + cellLength / 2 + boardY, cellLength / float(2.0), RED, Color{ 196,110,57,255 });
		}
		else if (iskChecked(board, castlingRights,lastMove) && (x + y) % 2 != 0) {
			DrawCircleGradient(x * cellLength + cellLength / 2 + boardX, y * cellLength + cellLength / 2 + boardY, cellLength / float(2.0), RED, Color{ 238,202,161,255 });
		}
		DrawTextureRec(*pieces, Rectangle{ 0,90,90,90 }, Vector2{ float(x) * cellLength + 5 + boardX ,float(y) * cellLength + 5 + boardY }, WHITE);
		break;
	case 'K':
		if (isKChecked(board, castlingRights,lastMove) && (x + y) % 2 == 0) {
			DrawCircleGradient(x * cellLength + cellLength / 2 + boardX, y * cellLength + cellLength / 2 + boardY, cellLength / float(2.0), RED, Color{ 196,110,57,255 });
		}
		else if (isKChecked(board, castlingRights,lastMove) && (x + y) % 2 != 0) {
			DrawCircleGradient(x * cellLength + cellLength / 2 + boardX, y * cellLength + cellLength / 2 + boardY, cellLength / float(2.0), RED, Color{ 238,202,161,255 });
		}
		DrawTextureRec(*pieces, Rectangle{ 0,0,90,90 }, Vector2{ float(x) * cellLength + 5 + boardX,float(y) * cellLength + 5 + boardY }, WHITE);
	}
}
void renderMousePosition(int cellLength,int boardX,int boardY) {
	std::pair<int, int> mousePosition = getMousePosition(cellLength, boardX, boardY);
	if (GetMouseX() <= boardX + (cellLength * 8) && GetMouseY() <= boardY + (cellLength * 8) && GetMouseX() > boardX && GetMouseY() > boardY) {
		DrawRectangleLinesEx(Rectangle{ float(mousePosition.first) * cellLength + boardX,float(mousePosition.second) * cellLength + boardY,float(cellLength),float(cellLength) }, 5, YELLOW);
	}
}
void renderPieceOnMouse(int cellLength, char type, Texture2D* pieces) {
	switch (type) {
	case 'p' : 
		DrawTextureRec(*pieces, Rectangle{ 460,90,90,90 }, OFFSET3, WHITE);
		break;
	case 'P' :
		DrawTextureRec(*pieces, Rectangle{ 460,0,90,90 }, OFFSET3, WHITE);
		break;
	case 'R' :
		DrawTextureRec(*pieces, Rectangle{ 370,0,90,90 }, OFFSET3, WHITE);
		break;
	case 'r' : 
		DrawTextureRec(*pieces, Rectangle{ 370,90,90,90 }, OFFSET3, WHITE);
		break;
	case 'N' : 
		DrawTextureRec(*pieces, Rectangle{ 280,0,90,90 }, OFFSET3, WHITE);
		break;
	case 'n' :
		DrawTextureRec(*pieces, Rectangle{ 280,90,90,90 }, OFFSET3, WHITE);
		break;
	case 'B' : 
		DrawTextureRec(*pieces, Rectangle{ 190,0,90,90 }, OFFSET3, WHITE);
		break;
	case 'b' :
		DrawTextureRec(*pieces, Rectangle{ 190,90,90,90 }, OFFSET3, WHITE);
		break;
	case 'Q' : 
		DrawTextureRec(*pieces, Rectangle{ 85,0,90,90 }, OFFSET4, WHITE);
		break;
	case 'q' :
		DrawTextureRec(*pieces, Rectangle{ 85,90,90,90 }, OFFSET4, WHITE);
		break;
	case 'K' : 
		DrawTextureRec(*pieces, Rectangle{ 0,0,90,90 }, OFFSET5, WHITE);
		break;
	case 'k' : 
		DrawTextureRec(*pieces, Rectangle{ 0,90,90,90 }, OFFSET5, WHITE);
		break;
	}
}

// a function to render the possible moves a piece can play
void renderPossibleMoves(std::pair<int, int> position,char piece, char board[8][8],int cellLength, int boardX, int boardY,char pieceOnMouse,bool castlingRights[4], std::pair<int,int> lastMove[2]) {
	char boardCostom[8][8];
	bool sideChecked;
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			boardCostom[a][b] = board[a][b];
		}
	}
	
	boardCostom[position.first][position.second] = pieceOnMouse;
	
	
	char boardAfter[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			copyBoard(boardAfter, boardCostom);
			boardAfter[j][i] = boardAfter[position.first][position.second];
			boardAfter[position.first][position.second] = ' ';
			sideChecked = isSideChecked(piece, boardAfter, castlingRights,lastMove);
			// if the possible move is not a capture
			if (isMoveValid(boardCostom[position.first][position.second], position, std::make_pair(j, i), boardCostom,castlingRights,lastMove) && board[j][i] == ' ' && !sideChecked) {

				DrawCircle(i * cellLength + cellLength/ 2 + boardX, j * cellLength + cellLength / 2 + boardY, float(cellLength/7.0),Color{170,170,170,170});
			}
			// else if the possible move is a capture
			else if (isMoveValid(boardCostom[position.first][position.second], position, std::make_pair(j, i), boardCostom,castlingRights,lastMove) && board[j][i] != ' ' && !sideChecked) {

				DrawRing(Vector2{ float(i * cellLength + cellLength * 0.5 + boardX) ,float(j * cellLength + cellLength * 0.5 + boardY) }, float(cellLength / 2.2), cellLength / float(2.0), 0, 360, 1, Color{ 170,170,170,170 });
			}
		}
	}
}

void renderBorder(int cellLength, int boardX, int boardY,Font* font) {
	float thickness = cellLength * 8 / float(32.0);
	std::string letters[8] = { "A","B", "C", "D", "E", "F", "G", "H" };
	std::string numbers[8] = { "1","2", "3", "4", "5", "6", "7", "8" };
	DrawRectangleLinesEx(Rectangle{ float(boardX) - thickness,float(boardY) - thickness,float(cellLength) * 8 + thickness*2,float(cellLength) * 8 + thickness*2 }, thickness, Color{ 98,55,34,255 });
	for (int i = 0; i < 8; i++) {
		DrawText(letters[i].c_str(), cellLength * i + cellLength * 0.5 + boardX - (thickness) / 2, boardY + cellLength * 8 +1, thickness - 1, WHITE);
		DrawText(numbers[7-i].c_str(), boardX + cellLength * 8 + 6, cellLength * i + cellLength * 0.5 + boardY - (thickness) / 2 + 2, thickness - 1, WHITE);
	}
	
}

void renderPieceLastPos(int x, int y, int cellLength, char type, Texture2D* pieces, char board[8][8], int boardX, int boardY) {
	switch (type) {
	case 'p': 
		DrawTextureRec(*pieces, Rectangle{ 460,90,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'P': 
		DrawTextureRec(*pieces, Rectangle{ 460,0,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'R': 
		DrawTextureRec(*pieces, Rectangle{ 370,0,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'r':
		DrawTextureRec(*pieces, Rectangle{ 370,90,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'N': 
		DrawTextureRec(*pieces, Rectangle{ 280,0,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'n': 
		DrawTextureRec(*pieces, Rectangle{ 280,90,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'B': 
		DrawTextureRec(*pieces, Rectangle{ 190,0,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'b': 
		DrawTextureRec(*pieces, Rectangle{ 190,90,90,90 }, OFFSET1, WEAKWHITE);
		break;
	case 'Q':
		DrawTextureRec(*pieces, Rectangle{ 85,0,90,90 }, OFFSET2, WEAKWHITE);
		break;
	case 'q': 
		DrawTextureRec(*pieces, Rectangle{ 85,90,90,90 }, OFFSET2, WEAKWHITE);
		break;
	case 'K': 
		DrawTextureRec(*pieces, Rectangle{ 0,0,90,90 }, OFFSET6, WEAKWHITE);
		break;
	case 'k':
		DrawTextureRec(*pieces, Rectangle{ 0,90,90,90 }, OFFSET6, WEAKWHITE);
		break;
	}
}

void renderPromotion(int boardX, int boardY, int cellLength, Texture2D* pieces, int x, char piece) {
	int y = 0;
	if (isUpperCase(piece)) {
		DrawRectangle(float(x) * cellLength + boardX, float(y) * cellLength + boardY, cellLength, cellLength * 4,GRAY);
		DrawTextureRec(*pieces, Rectangle{ 85,0,90,90 }, Vector2{float(boardX) + cellLength * x,float(boardY)+5 + cellLength*y}, WHITE);
		y = 1;
		DrawTextureRec(*pieces, Rectangle{ 360,0,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
		y = 2;
		DrawTextureRec(*pieces, Rectangle{ 180,0,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
		y = 3;
		DrawTextureRec(*pieces, Rectangle{ 270,0,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
	}
	else if (isLowerCase(piece)) {
		y = 4;
		DrawRectangle(float(x) * cellLength + boardX, float(y) * cellLength + boardY, cellLength, cellLength * 4, GRAY);
		DrawTextureRec(*pieces, Rectangle{ 265,90,90,90 }, Vector2{ float(boardX) + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
		y = 5;
		DrawTextureRec(*pieces, Rectangle{ 180,90,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
		y = 6;
		DrawTextureRec(*pieces, Rectangle{ 360,90,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
		y = 7;
		DrawTextureRec(*pieces, Rectangle{ 90,90,90,90 }, Vector2{ float(boardX) + 5 + cellLength * x,float(boardY) + 5 + cellLength * y }, WHITE);
	}
}