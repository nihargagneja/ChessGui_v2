//
// Created by Nihar Gagneja on 9/30/24.
//

#include "PieceSliding.h"
#include "../ChessBoard.h"




// DEPRECATED: PIECES NOW QUERY THE BOARD FOR THEIR POSITION USING THEIR ID
std::vector<ChessMove> PieceSliding::availableMoves(Vector2i position) const {
    std::vector<ChessMove> moves = {};

    for (auto moveDir : getMoveDirections()) {
        bool directionTerminates = false;
        Vector2i destination = position;

        do {
            destination = destination + moveDir;

            // bounds check
            if(!ChessBoard::inBounds(destination)) {
                directionTerminates = true;
                continue;
            }

            auto otherPiece = m_board->getPieceAt(destination);

            // possibility: move into empty square
            if(otherPiece == nullptr) {
                moves.push_back({position, destination, MoveType::INTO_EMPTY});
            }

            // possibility: capture piece of another color
            else if (!sameColorAs(otherPiece)) {
                moves.push_back({position, destination, MoveType::CAPTURE});
                directionTerminates = true;
            }

            else if (sameColorAs(otherPiece)) {
                directionTerminates = true;
            }
        } while(!directionTerminates);
    }

    return moves;
}

std::vector<ChessMove> PieceSliding::availableMoves() const {
    std::vector<ChessMove> moves = {};
    auto positionOnBoard = m_board->getPiecePositionByID(m_id);

    for (auto moveDir : getMoveDirections()) {
        bool directionTerminates = false;
        Vector2i destination = positionOnBoard;

        do {
            destination = destination + moveDir;

            // bounds check
            if(!ChessBoard::inBounds(destination)) {
                directionTerminates = true;
                continue;
            }

            auto otherPiece = m_board->getPieceAt(destination);

            // possibility: move into empty square
            if(otherPiece == nullptr) {
                moves.push_back({positionOnBoard, destination, MoveType::INTO_EMPTY});
            }

            // possibility: capture piece of another color
            else if (!sameColorAs(otherPiece)) {
                moves.push_back({positionOnBoard, destination, MoveType::CAPTURE});
                directionTerminates = true;
            }

            else if (sameColorAs(otherPiece)) {
                directionTerminates = true;
            }
        } while(!directionTerminates);
    }

    return moves;
}

