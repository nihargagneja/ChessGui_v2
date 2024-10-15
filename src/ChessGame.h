//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "ChessBoard.h"
#include "GUIState.h"


class ChessGame {
private:
    // Constants for drawing the board
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const int TILE_WIDTH = WINDOW_WIDTH / 8;
    const int TILE_HEIGHT = WINDOW_HEIGHT / 8;

    ChessBoard m_board;
    GUIState m_guiState;

    // internal functions used to run the game
    void initGame();
    void draw();

    // input processing
    void processInput();
        void onMouseLeftClick();

    void gameLoop();

    void update();

    void terminateGame();

public:
    void run();

};



#endif //CHESSGAME_H
