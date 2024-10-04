//
// Created by Nihar Gagneja on 9/30/24.
//

#include "ChessGame.h"

#include <iostream>
#include <ostream>
#include <raylib.h>

#include "GUIState.h"

void ChessGame::run() {
    initGame();
    gameLoop();
    terminateGame();
}

void ChessGame::initGame() {
    InitWindow(800, 800, "Hello World");
    SetTargetFPS(60);

    m_board.setUp();

    auto move = ChessMove{3, 3, 4, 4, MoveType::CAPTURE};
    m_board.executeMove(move);
}

void ChessGame::gameLoop() {
    // next piece of this is really to be able to move pieces around or it will be hard to debug

    bool enterPressed = false;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        update();
        draw();
        processInput();

        EndDrawing();
    }
}

void ChessGame::update() {

}

void ChessGame::draw() {
    m_board.draw(m_guiState.selectedPiece); // draw the chess board

    // draw other things - timer, etc

}

void ChessGame::processInput() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        onMouseLeftClick();
    }
}

void ChessGame::onMouseLeftClick() {
        auto tileUnderMouse = Vector2i {GetMouseX() / TILE_WIDTH,GetMouseY() / TILE_HEIGHT };
        std::cout << tileUnderMouse.x << " " << tileUnderMouse.y << std::endl;

        if(m_board.pieceExistsAt( tileUnderMouse ) && m_guiState.selectedPiece == nullptr) {
            m_guiState.selectedPiece = m_board.getPieceAt(tileUnderMouse);
            m_guiState.positionOfSelectedPiece = tileUnderMouse;
        } else if (m_board.pieceExistsAt(tileUnderMouse) && m_guiState.selectedPiece != nullptr) {
            m_guiState.selectedPiece = m_board.getPieceAt(tileUnderMouse);
            m_guiState.positionOfSelectedPiece = tileUnderMouse;
        }
}

void ChessGame::terminateGame() {
    CloseWindow();
}
