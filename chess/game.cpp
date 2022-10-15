#include "game.h"
#include "render.h"
#include "string.h"
#include "raylib.h"
#include "utilities.h"
#include <iostream>
void game::start() {
    const int screenWidth = 850;
    const int screenHeight = 850;
    int boardX = 25;
    int boardY = 25;
    int promotionFile = -1;
    char pieceOnMouse = ' ';
    bool turn = 1; // 1 for white, 0 for black
    bool gameOver = false;
    std::pair<int, int> pieceLastPos;
    std::pair<int,int> lastMove[2] = {std::make_pair(-1,-1),std::make_pair(-1,-1) };

    // castlingRights[0] = can white castle king side
    // castlingRights[1] = can white castle queen side
    // castlingRights[2] = can black castle king side
    // castlingRights[3] = can black castle queen side
    bool castlingRights[] = {true,true,true,true};

    InitWindow(screenWidth, screenHeight, "chess");
    InitAudioDevice();
    Sound fxMove = LoadSound("../assets/move.mp3");         
    Sound fxCapture = LoadSound("../assets/capture.mp3");
    Texture2D pieces = LoadTexture("../assets/pieces.png");
    Font font = LoadFontEx("font.ttf", 640, 0, 79);
    //SetTargetFPS(144);               
    char board[8][8] = { {'r','n','b','q','k','b','n','r'},
                        {'p','p','p','p','p','p','p','p'},
                        {' ',' ',' ',' ',' ',' ',' ',' '},
                        {' ',' ',' ',' ',' ',' ',' ',' '},
                        {' ',' ',' ',' ',' ',' ',' ',' '},
                        {' ',' ',' ',' ',' ',' ',' ',' '},
                        {'P','P','P','P','P','P','P','P'},
                        {'R','N','B','Q','K','B','N','R'}};
    // read fen notation
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board,&turn,castlingRights);
    // main loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            renderBoard(boardX, boardY, 100);
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    renderPiece(j , i, 100, board[i][j], &pieces,board,boardX,boardY, castlingRights,lastMove);
                }
            }
            renderBorder(100, boardX, boardY,&font);
            if (promotionFile == -1) {
                renderMousePosition(100, boardX, boardY);
                renderPossibleMoves(pieceLastPos, pieceOnMouse, board, 100, boardX, boardY, pieceOnMouse, castlingRights,lastMove);
                renderPieceOnMouse(100, pieceOnMouse, &pieces);
                renderPieceLastPos(pieceLastPos.second, pieceLastPos.first, 100, pieceOnMouse, &pieces, board, boardX, boardY);
            }
            else {
                if (!turn) { 
                    renderPromotion(boardX, boardY, 100, &pieces, promotionFile, 'P'); 
                    promotionFile = handlePromotion('P', promotionFile, board, boardX, boardY, 100);
                }
                if (turn) {
                    renderPromotion(boardX, boardY, 100, &pieces, promotionFile, 'p');
                    promotionFile = handlePromotion('p', promotionFile, board, boardX, boardY, 100);
                }
                renderMousePosition(100, boardX, boardY);
            }
            
        EndDrawing();

        if (!gameOver && promotionFile == -1) promotionFile = movePieceToMouse(100, &pieceOnMouse, board, &pieceLastPos, &turn,boardX,boardY,castlingRights,fxMove,fxCapture,lastMove);
        

        if (isBlackMated(board,castlingRights,lastMove) && !gameOver && pieceOnMouse == ' ') {
            std::cout << "White won by checkmate" << std::endl;
            gameOver = true;
        }
        else if (isWhiteMated(board, castlingRights,lastMove) && !gameOver && pieceOnMouse == ' ') {
            std::cout << "Black won by checkmate" << std::endl;
            gameOver = true;
        }
        else if (isDrawByMaterial(board) && !gameOver && pieceOnMouse == ' ') {
            std::cout << "Draw by insufficient material" << std::endl;
            gameOver = true;
        }
        /*
        else if (isDrawByStaleMate(board,castlingRights) && !gameOver && pieceOnMouse == ' ') {
            std::cout << "Draw by stalemate" << std::endl;
            gameOver = true;
        }
        */
    }
    CloseWindow();
    UnloadSound(fxMove);    
    UnloadSound(fxCapture);
    UnloadTexture(pieces);
    UnloadFont(font);
}