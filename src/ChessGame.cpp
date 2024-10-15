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

    // auto move = ChessMove{3, 3, 4, 4, MoveType::CAPTURE};
    // m_board.executeMove(move);
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

void ChessGame::draw() {
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
    auto pieceAlreadySelected = m_guiState.getSelectedPiece();

    // if no piece selected, and clicking on an empty square, we're done.
    if(!pieceAlreadySelected && !pieceClickedOn) {
        return;
    }

    // if no piece is selected, and we click on a piece, select it, and we're done.
    if(!pieceAlreadySelected && pieceClickedOn) {
        m_guiState.selectPiece(pieceClickedOn);
        return;
    }

    // if piece selected and click on the same piece, deselect it, and we're done. This logic should actually already be
    // covered by the legalMovesAvailableTo() logic, but it has been helpful to isolate this case when debugging.
    if(pieceAlreadySelected && pieceClickedOn && (pieceClickedOn->getID() == pieceAlreadySelected->getID())) {
        m_guiState.deselectPiece();
        return;
    }

    // if a piece is already selected, look for a matching move and execute it if there is one
    // otherwise just deselect the piece
    auto movesAvailableToSelectedPiece = m_board.legalMovesOf(pieceAlreadySelected);
    for (auto move : movesAvailableToSelectedPiece) {
        if (move.endPosition == tileUnderMouse) {
            m_board.executeMove(move);
            break;
        }
    }
    m_guiState.deselectPiece();
    return;
}

void ChessGame::terminateGame() {
    CloseWindow();
}
