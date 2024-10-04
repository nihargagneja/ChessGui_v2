//
// Created by Nihar Gagneja on 10/2/24.
//

#include "PieceKnight.h"

#include <raylib.h>
#include <vector>

#include "ChessBoard.h"

std::vector<ChessMove> PieceKnight::availableMoves(Vector2i position) const {
    std::vector<ChessMove> moves;

    Vector2i destinations[8] = {
        { position.x + 1, position.y + 2 }, // option 1, row and column
        { position.x + 1, position.y - 2 }, // option 2, row and column
        { position.x - 1, position.y + 2 }, // ...
        { position.x - 1, position.y - 2 },
        { position.x + 2, position.y + 1 },
        { position.x + 2, position.y - 1 },
        { position.x - 2, position.y + 1 },
        { position.x - 2, position.y - 1 },
    };

    for (auto dest : destinations) {
        // bounds check (is there a better place for this?)
        if(!ChessBoard::inBounds(dest)) continue;
        auto otherPiece = m_board->getPieceAt(dest);

        // possibility #1: move into empty square
        if (otherPiece == nullptr) {
            moves.push_back(ChessMove {position.x, position.y, dest.x, dest.y, MoveType::INTO_EMPTY});
            continue;
        }

        // possibility #2: capture piece of another color
        if (!sameColorAs(otherPiece)) {
            moves.push_back(ChessMove {position.x, position.y, dest.x, dest.y, MoveType::CAPTURE});;
            continue;
        }

        // (not possible: taking own piece)
    }

    return moves;
}

std::string PieceKnight::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "K" : "k";
}

PieceType PieceKnight::getPieceType() const {
    return PieceType::KNIGHT;
}
