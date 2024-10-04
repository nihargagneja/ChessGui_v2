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
    KING = 0,  QUEEN  = 1, PAWN   = 2,
    ROOK = 3,  BISHOP = 4, KNIGHT = 5,
};

enum class PieceColor {
    WHITE_COLOR = 0,
    BLACK_COLOR = 1
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
