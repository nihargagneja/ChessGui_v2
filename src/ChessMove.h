//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <Vector2i.h>
#include <vector>

enum class PieceColor;

enum class MoveType {
    INTO_EMPTY,
    CAPTURE,
    CASTLE
};

struct ChessMove {
public:
    Vector2i startPosition;
    Vector2i endPosition;
    MoveType type;

private:
    // doesn't work, no way to tell the color of the piece that the move is from lmao
    // static std::vector<ChessMove> filterByColor(const std::vector<ChessMove>& chessMoves, PieceColor pieceColor) {
    //     std::vector<ChessMove> filteredChessMoves = {};
    //
    //     filteredChessMoves.reserve(chessMoves.size());
    //     for (auto move: chessMoves) {
    //         if (movel)
    //         filteredChessMoves.push_back(move);
    //     }
    //     filteredChessMoves.shrink_to_fit();
    //
    //     return filteredChessMoves;
    // };
};


#endif //CHESSMOVE_H
