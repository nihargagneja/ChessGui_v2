//
// Created by Nihar Gagneja on 9/30/24.
//

#include "Piece.h"
#include "../src/ChessBoard.h"



bool Piece::sameColorAs(const Piece* otherPiece) const {
    return this->getColor() == otherPiece->getColor();
}
