//
// Created by Nihar Gagneja on 10/1/24.
//

#ifndef PIECEROOK_H
#define PIECEROOK_H
#include "PieceSliding.h"


class PieceRook : public PieceSliding {
protected:

public:
    PieceRook(PieceColor color, const ChessBoard *board) : PieceSliding(color, board) {}

    [[nodiscard]] std::string getSymbol() const override;

    [[nodiscard]] std::vector<Vector2i> getMoveDirections() const override;

    [[nodiscard]] PieceType getPieceType() const override;

    [[nodiscard]] std::shared_ptr<Piece> xerox() const override { return std::make_shared<PieceRook>(*this); }
};



#endif //PIECEROOK_H
