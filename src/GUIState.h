//
// Created by Nihar Gagneja on 10/3/24.
//

#ifndef GUISTATE_H
#define GUISTATE_H

#include "ChessPieces/Piece.h"

struct GUIState {
public:
    const Piece* selectedPiece;
    Vector2i positionOfSelectedPiece;
    GUIState() : selectedPiece(nullptr) {}
};



#endif //GUISTATE_H
