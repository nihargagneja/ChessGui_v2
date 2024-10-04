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

    static int m_idCounter; // each piece gets a serial id to query its position on the board
    int m_id;

public:
    Piece(const PieceColor color, const ChessBoard* board) : m_color(color), m_board(board) {
        m_id = m_idCounter++;
    };
    virtual ~Piece() = default;

    // information
    [[nodiscard]] virtual std::vector<ChessMove> availableMoves(Vector2i position) const = 0; // DEPRECATED
    [[nodiscard]] virtual std::vector<ChessMove> availableMoves() const = 0; // USE THIS AND BOARD FOR POSITION USING ID
    [[nodiscard]] virtual PieceType getPieceType() const = 0;
    [[nodiscard]] bool sameColorAs(const Piece* otherPiece) const;
    [[nodiscard]] Vector2i getPositionFromBoard();

    // simple getters
    [[nodiscard]] virtual std::string getSymbol() const = 0;
    [[nodiscard]] PieceColor getColor() const { return m_color; }
    [[nodiscard]] int getID() const { return m_id; }
};



#endif //PIECE_H
