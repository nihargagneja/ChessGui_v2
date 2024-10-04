//
// Created by Nihar Gagneja on 10/2/24.
//

#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"


class PiecePawn : public Piece {
private:
    bool m_hasMoved = false;

protected:

public:
    PiecePawn(PieceColor color, const ChessBoard *board) : Piece(color, board) {}

    [[nodiscard]] std::vector<ChessMove> availableMoves(Vector2i position) const override;
    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] PieceType getPieceType() const override;
};



#endif //PAWN_H
