//
// Created by Nihar Gagneja on 10/2/24.
//

#include "PiecePawn.h"
#include "ChessBoard.h"

#include <vector>


std::vector<ChessMove> PiecePawn::availableMoves(Vector2i position) const {
    std::vector<ChessMove> moves;

    // FORWARD MOVE BY ONE IF POSSIBLE
    Vector2i destination;
    destination.x = position.x;
    if (m_color == PieceColor::WHITE_COLOR) {
        destination.y = position.y - 1;
    } else {
        destination.y = position.y + 1;
    }

    // bounds check                       // and moving into empty square
    if (ChessBoard::inBounds(destination) && m_board->getPieceAt(destination) == nullptr) {
        moves.push_back(ChessMove{position.x, position.y, destination.x, destination.y, MoveType::INTO_EMPTY});
    }

    // TWO FORWARD IF FIRST MOVE
    if (m_color == PieceColor::BLACK_COLOR && position.y == 1 ||
        m_color == PieceColor::WHITE_COLOR && position.y == 6) {
        destination.x = position.x;
        if (m_color == PieceColor::WHITE_COLOR) {
            destination.y = position.y - 2;
        } else {
            destination.y = position.y + 2;
        }

        // bounds check                       // and moving into empty square
        if (ChessBoard::inBounds(destination) && m_board->getPieceAt(destination) == nullptr) {
            moves.push_back(ChessMove{position.x, position.y, destination.x, destination.y, MoveType::INTO_EMPTY});
        }
    }

    // DIAGONAL CAPTURE IF POSSIBLE
    Vector2i diagonals[2]; // 2 diagonal moves, 2 coordinates (row/column)
    if (m_color == PieceColor::WHITE_COLOR) {
        diagonals[0].x = position.x - 1;
        diagonals[0].y = position.y - 1;
        diagonals[1].x = position.x + 1;
        diagonals[1].y = position.y - 1;
    } else {
        diagonals[0].x = position.x - 1;
        diagonals[0].y = position.y + 1;
        diagonals[1].x = position.x + 1;
        diagonals[1].y = position.y + 1;
    }

    for(auto diag : diagonals) {
        // bounds check
        if (!ChessBoard:: inBounds(diag)) { continue; }
        auto otherPiece = m_board->getPieceAt(diag);

            // there's a piece there and can capture if from other team
        if (otherPiece != nullptr && !sameColorAs(otherPiece)) {
            moves.push_back(ChessMove {position.x, position.y, destination.x, destination.y, MoveType::CAPTURE});
        }
    }

    return moves;
}

std::vector<ChessMove> PiecePawn::availableMoves() const {
    std::vector<ChessMove> moves;

    auto position = m_board->getPiecePositionByID(m_id);

    // FORWARD MOVE BY ONE IF POSSIBLE
    Vector2i destination;
    destination.x = position.x;
    if (m_color == PieceColor::WHITE_COLOR) {
        destination.y = position.y - 1;
    } else {
        destination.y = position.y + 1;
    }

    // bounds check                       // and moving into empty square
    if (ChessBoard::inBounds(destination) && m_board->getPieceAt(destination) == nullptr) {
        moves.push_back(ChessMove{position.x, position.y, destination.x, destination.y, MoveType::INTO_EMPTY});
    }

    // TWO FORWARD IF FIRST MOVE
    if (m_color == PieceColor::BLACK_COLOR && position.y == 1 ||
        m_color == PieceColor::WHITE_COLOR && position.y == 6) {
        destination.x = position.x;
        if (m_color == PieceColor::WHITE_COLOR) {
            destination.y = position.y - 2;
        } else {
            destination.y = position.y + 2;
        }

        // bounds check                       // and moving into empty square
        if (ChessBoard::inBounds(destination) && m_board->getPieceAt(destination) == nullptr) {
            moves.push_back(ChessMove{position.x, position.y, destination.x, destination.y, MoveType::INTO_EMPTY});
        }
    }

    // DIAGONAL CAPTURE IF POSSIBLE
    Vector2i diagonals[2]; // 2 diagonal moves, 2 coordinates (row/column)
    if (m_color == PieceColor::WHITE_COLOR) {
        diagonals[0].x = position.x - 1;
        diagonals[0].y = position.y - 1;
        diagonals[1].x = position.x + 1;
        diagonals[1].y = position.y - 1;
    } else {
        diagonals[0].x = position.x - 1;
        diagonals[0].y = position.y + 1;
        diagonals[1].x = position.x + 1;
        diagonals[1].y = position.y + 1;
    }

    for(auto diag : diagonals) {
        // bounds check
        if (!ChessBoard:: inBounds(diag)) { continue; }
        auto otherPiece = m_board->getPieceAt(diag);

            // there's a piece there and can capture if from other team
        if (otherPiece != nullptr && !sameColorAs(otherPiece)) {
            moves.push_back(ChessMove {position.x, position.y, destination.x, destination.y, MoveType::CAPTURE});
        }
    }

    return moves;
}

std::string PiecePawn::getSymbol() const {
    return m_color == PieceColor::WHITE_COLOR ? "P" : "p";
}

PieceType PiecePawn::getPieceType() const {
    return PieceType::PAWN;
}
