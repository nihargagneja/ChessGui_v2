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

        // if a piece is already selected
        if (m_guiState.pieceIsSelected()) {
            // check if it's the same piece as already selected, and if so, deselect it
            if (tileUnderMouse == m_guiState.selectedPiece->getPositionFromBoard()) {
                m_guiState.deselectPiece();
            }

            // if a blank tile was clicked
            else if (!m_board.getPieceAt(tileUnderMouse)) {
                auto requestedMove = ChessMove {
                    m_guiState.selectedPiece->getPositionFromBoard(),
                    tileUnderMouse,
                    MoveType::INTO_EMPTY
                };

                // chess pieces available moves just tells you what moves are available
                // board filters those moves with
                // legalMovesAvailableTo();
                if (m_board.moveIsLegalFor(m_guiState.activePlayer, requestedMove)) {
                    m_board.executeMove(requestedMove);
                    m_guiState.deselectPiece();
                } else {
                    m_guiState.deselectPiece();
                }


            }

            // if no piece is selected
            else {
                // if the tile has a piece, select it
                if(m_board.getPieceAt(tileUnderMouse)) {
                    m_guiState.selectPiece(m_board.getPieceAt(tileUnderMouse));
                }

                // if there's no piece, don't select anything
            }


        // if no piece is already selected
        } else {
            if(m_board.pieceExistsAt( tileUnderMouse )) {
                m_guiState.selectedPiece = m_board.getPieceAt(tileUnderMouse);
                m_guiState.positionOfSelectedPiece = tileUnderMouse;

                // another consideration needs to be added here - what if you click on a piece that has no possible moves?
                // Maybe we don't want to select it in that case since it would be hard to "deselect" if you cant tell which it is!

            } else if (m_board.pieceExistsAt(tileUnderMouse) && m_guiState.selectedPiece != nullptr) {
                m_guiState.selectedPiece = m_board.getPieceAt(tileUnderMouse);
                m_guiState.positionOfSelectedPiece = tileUnderMouse;
            }
        }
}

void ChessGame::terminateGame() {
    CloseWindow();
}
