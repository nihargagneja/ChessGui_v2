//
// Created by Nihar Gagneja on 9/30/24.
//


#include <iostream>
#include <ostream>
#include <raylib.h>

#include "ChessGame.h"
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
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // GAME LOOP CORE
        update();
        draw();
        processInput();

        EndDrawing();
    }
}

void ChessGame::update() {
    // check the game state - checks winner loser
}

void ChessGame::draw() const {
    m_board.draw(m_guiState.getSelectedPiece()); // draw the chess board

    // draw other things - timer, etc

}

void ChessGame::processInput() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        onMouseLeftClick();
    }
}

void ChessGame::onMouseLeftClick() {
    const auto tileUnderMouse = Vector2i {GetMouseX() / TILE_WIDTH,GetMouseY() / TILE_HEIGHT };
    std::cout << tileUnderMouse.x << " " << tileUnderMouse.y << std::endl;

    auto pieceClickedOn = m_board.getPieceAt(tileUnderMouse);

    // if clicked on a piece and no piece selected, select it
    if(pieceClickedOn && !m_guiState.pieceIsSelected()) {
        m_guiState.selectPiece(pieceClickedOn);
    }

    // if clicked on a piece and a piece is already selected
    else if(pieceClickedOn && m_guiState.pieceIsSelected()) {
        // if they clicked on the piece that's already selected, deselect it
        if (pieceClickedOn->getPositionFromBoard() == tileUnderMouse) {
            m_guiState.deselectPiece();
        }
    }

    else if (!pieceClickedOn && m_guiState.pieceIsSelected()) {
        std::cout << "reached here" ;
        // go through the valid moves for the selected piece and find a match based on the destination tile only
        for (auto validMove : m_board.legalMovesAvailableTo(m_guiState.getSelectedPiece())) {
            if (validMove.endPosition == tileUnderMouse) {
                std::cout << "valid move executing";
                m_board.executeMove(validMove);
                break;
            }
        }
        m_guiState.deselectPiece();
    }
}

void ChessGame::terminateGame() {
    CloseWindow();
}
