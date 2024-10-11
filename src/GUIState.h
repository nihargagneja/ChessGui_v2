//
// Created by Nihar Gagneja on 10/3/24.
//

#ifndef GUISTATE_H
#define GUISTATE_H

#include "ChessPieces/Piece.h"

class GUIState {
private:
    std::shared_ptr<Piece> selectedPiece = nullptr;
    PieceColor activePlayer = PieceColor::WHITE_COLOR;

public:
    [[nodiscard]] bool pieceIsSelected() const { return selectedPiece != nullptr; }
    void selectPiece(const std::shared_ptr<Piece> &pieceToSelect) { selectedPiece = pieceToSelect; }
    void deselectPiece() { selectedPiece = nullptr; }
    [[nodiscard]] std::shared_ptr<Piece> getSelectedPiece() const { return selectedPiece; }
};



#endif //GUISTATE_H
