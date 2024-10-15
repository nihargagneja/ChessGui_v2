//
// Created by Nihar Gagneja on 10/2/24.
//

#ifndef PIECEKNIGHT_H
#define PIECEKNIGHT_H
#include "Piece.h"


class PieceKnight : public Piece {
protected:

public:
    PieceKnight(PieceColor color, const ChessBoard *board) : Piece(color, board) {}
    [[nodiscard]] std::vector<ChessMove> getAvailableMoves(Vector2i position) const override;
    [[nodiscard]] std::vector<ChessMove> getAvailableMoves() const override;

    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override {
        return std::make_shared<PieceKnight>(*this);
    }

    [[nodiscard]] int getPointsValue() const override { return 3; }
};



#endif //PIECEKNIGHT_H
