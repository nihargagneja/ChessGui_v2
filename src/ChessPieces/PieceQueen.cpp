//
// Created by Nihar Gagneja on 10/1/24.
//

#include "PieceQueen.h"

std::string PieceQueen::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "Q" : "q";
}

std::vector<Vector2i> PieceQueen::getMoveDirections() const {
    return {
        // Rook-style movements
        Vector2i {+1, +0},
        Vector2i {-1, +0},
        Vector2i {+0, +1},
        Vector2i {+0, -1},

        // Bishop-style movements
        Vector2i {+1, +1},
        Vector2i {+1, -1},
        Vector2i {-1, +1},
        Vector2i {-1, -1}
    };
}

PieceType PieceQueen::getPieceType() const {
    return PieceType::QUEEN;
}
