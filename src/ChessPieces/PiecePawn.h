//
// Created by Nihar Gagneja on 10/2/24.
//

#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"


class PiecePawn : public Piece {
private:
    // bool m_hasMoved = false; // refactored availableMoves to use the color and column of the pawn rather
                                // having more complexity with a member variable

protected:

public:
    PiecePawn(PieceColor color, const ChessBoard *board) : Piece(color, board) {}

    [[nodiscard]] std::vector<ChessMove> availableMoves(Vector2i position) const override;
    [[nodiscard]] std::vector<ChessMove> availableMoves() const override;

    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override { return std::make_shared<PiecePawn>(*this); }
};



#endif //PAWN_H
