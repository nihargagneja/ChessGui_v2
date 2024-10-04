//
// Created by Nihar Gagneja on 10/2/24.
//

#include "PieceKing.h"

#include <raylib.h>
#include <vector>

#include "ChessBoard.h"

std::vector<ChessMove> PieceKing::availableMoves(Vector2i position) const {
    std::vector<ChessMove> moves;

    Vector2i destinations[8] = {
        Vector2i(position.x - 1, position.y - 1),
        Vector2i(position.x + 0, position.y - 1),
        Vector2i(position.x + 1, position.y - 1),
        Vector2i(position.x + 1, position.y + 0),
        Vector2i(position.x + 1, position.y + 1),
        Vector2i(position.x + 0, position.y + 1),
        Vector2i(position.x - 1, position.y + 1),
        Vector2i(position.x - 1, position.y + 0)
    };

    for (auto dest : destinations) {
        // bounds check before we check the tile
        if(!ChessBoard::inBounds(dest)) continue;
        auto otherPiece = m_board->getPieceAt(dest);

        // possibility #1: move into empty square
        if (otherPiece == nullptr) {
            moves.push_back(ChessMove{position.x, position.y, dest.x, dest.y, MoveType::INTO_EMPTY});
        }

        // possibility #2: capture piece of another color
        else if (!sameColorAs(otherPiece)) {
            moves.push_back(ChessMove{position.x, position.y, dest.x, dest.y, MoveType::CAPTURE});
        }

        // (not possible: taking own piece)
        else {}
    }

    return moves;
}

std::string PieceKing::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "W" : "w";
}

PieceType PieceKing::getPieceType() const {
    return PieceType::KING;
}
