//
// Created by Nihar Gagneja on 9/30/24.
//

#include "Piece.h"
#include "../src/ChessBoard.h"

int Piece::m_idCounter = 0;

bool Piece::sameColorAs(const Piece* otherPiece) const {
    return this->getColor() == otherPiece->getColor();
}

Vector2i Piece::getPositionFromBoard() {
    return m_board->getPiecePositionByID(m_id);
}
