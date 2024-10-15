//
// Created by Nihar Gagneja on 10/1/24.
//

#ifndef PIECEQUEEN_H
#define PIECEQUEEN_H
#include "PieceSliding.h"


class PieceQueen : public PieceSliding {
public:
    PieceQueen(PieceColor color, const ChessBoard *board) : PieceSliding(color, board) {}

    [[nodiscard]] std::string getSymbol() const override;
    [[nodiscard]] std::vector<Vector2i> getMoveDirections() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override {
        return std::make_shared<PieceQueen>(*this);
    }

    [[nodiscard]] int getPointsValue() const override { return 9; }
};



#endif //PIECEQUEEN_H
