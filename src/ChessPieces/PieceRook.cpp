//
// Created by Nihar Gagneja on 10/1/24.
//

#include "PieceRook.h"

std::string PieceRook::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "R" : "r";
}

std::vector<Vector2i> PieceRook::getMoveDirections() const {
    return {
        Vector2i {+1, +0},
        Vector2i {-1, +0},
        Vector2i {+0, +1},
        Vector2i {+0, -1},
    };
}

PieceType PieceRook::getPieceType() const {
    return PieceType::ROOK;
}
