//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "Vector2i.h"
#include "ChessMove.h"

class ChessBoard;

enum class PieceType {
    KING,  QUEEN,  PAWN,
    ROOK,  BISHOP, KNIGHT,
};

enum class PieceColor {
    WHITE_COLOR,
    BLACK_COLOR
};

class Piece {
protected:
    PieceColor m_color;
    const ChessBoard* m_board;

public:
    Piece(const PieceColor color, const ChessBoard* board) : m_color(color), m_board(board) {};
    virtual ~Piece() = default;

    // information
    [[nodiscard]] virtual std::vector<ChessMove> availableMoves(Vector2i position) const = 0;
    [[nodiscard]] virtual PieceType getPieceType() const = 0;
    [[nodiscard]] bool sameColorAs(const Piece* otherPiece) const;

    // getters
    [[nodiscard]] virtual std::string getSymbol() const = 0;
    [[nodiscard]] PieceColor getColor() const { return m_color; }
};



#endif //PIECE_H
