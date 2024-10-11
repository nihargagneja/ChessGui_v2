//
// Created by Nihar Gagneja on 10/3/24.
//

#ifndef GUISTATE_H
#define GUISTATE_H

#include "ChessPieces/Piece.h"

struct GUIState {
public:
    Piece* selectedPiece;
    Vector2i positionOfSelectedPiece;
    PieceColor activePlayer = PieceColor::WHITE_COLOR;
    GUIState() : selectedPiece(nullptr) {}

    [[nodiscard]] bool pieceIsSelected() const { return selectedPiece != nullptr; }
    void selectPiece(Piece* const pieceToSelect) { selectedPiece = pieceToSelect; }
    void deselectPiece() { selectedPiece = nullptr; }
};



#endif //GUISTATE_H
