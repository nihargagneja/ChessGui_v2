//
// Created by Nihar Gagneja on 10/2/24.
//

#ifndef PIECEKING_H
#define PIECEKING_H
#include "Piece.h"


class PieceKing : public Piece {
protected:

public:
    PieceKing(PieceColor color, const ChessBoard *board) : Piece(color, board) {}

    [[nodiscard]] std::vector<ChessMove> availableMoves(Vector2i position) const override;
    [[nodiscard]] std::vector<ChessMove> availableMoves() const override;

    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override { return std::make_shared<PieceKing>(*this); }
};



#endif //PIECEKING_H
