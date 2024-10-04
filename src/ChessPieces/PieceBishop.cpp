//
// Created by Nihar Gagneja on 10/1/24.
//

#include "PieceBishop.h"

std::vector<Vector2i> PieceBishop::getMoveDirections() const {
    return {
        Vector2i {+1, +1},
        Vector2i {+1, -1},
        Vector2i {-1, +1},
        Vector2i {-1, -1},
    };
}

std::string PieceBishop::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "B" : "b";
}

PieceType PieceBishop::getPieceType() const {
    return PieceType::BISHOP;
}

