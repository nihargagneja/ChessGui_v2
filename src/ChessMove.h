//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <Vector2i.h>
#include <vector>

#include "ChessPieces/Piece.h"
#include "ChessPieces/Piece.h"

enum class PieceType;
enum class PieceColor;

enum class MoveType {
    INTO_EMPTY,
    CAPTURE,
    CASTLE,
    UNKNOWN
};

struct ChessMove {
public:
    Vector2i startPosition;
    Vector2i endPosition;
    MoveType type;

    // Utility functions
    bool operator==(const ChessMove &other) const {
        return  startPosition == other.startPosition &&
                endPosition   == other.endPosition &&
                type          == other.type;
    }

    [[nodiscard]] std::string toString() const {
        std::string moveTypeStr;
        switch (type) {
            case MoveType::INTO_EMPTY: moveTypeStr = "INTO_EMPTY"; break;
            case MoveType::CAPTURE: moveTypeStr = "CAPTURE"; break;
            case MoveType::CASTLE: moveTypeStr = "CASTLE"; break;
            case MoveType::UNKNOWN: moveTypeStr = "UNKNOWN"; break;
        }
        return "Move from (" + std::to_string(startPosition.x) + ", " + std::to_string(startPosition.y) +
                    ") to (" + std::to_string(endPosition.x) + ", " + std::to_string(endPosition.y) +
                    ") of type " + moveTypeStr;
    }
};


#endif //CHESSMOVE_H
