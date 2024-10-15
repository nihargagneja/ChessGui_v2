//
// Created by Nihar Gagneja on 10/1/24.
//

#ifndef PIECEBISHOP_H
#define PIECEBISHOP_H
#include "PieceSliding.h"


class PieceBishop : public PieceSliding {
protected:

public:
    PieceBishop(const PieceColor color, const ChessBoard *board) : PieceSliding(color, board) {}
    std::vector<Vector2i> getMoveDirections() const override;
    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override {
        return std::make_shared<PieceBishop>(*this);
    }

    [[nodiscard]] int getPointsValue() const override { return 3; }
};



#endif //PIECEBISHOP_H
