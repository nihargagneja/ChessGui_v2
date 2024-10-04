//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef SLIDINGPIECE_H
#define SLIDINGPIECE_H
#include <vector>
#include "Piece.h"


class PieceSliding : public Piece {
protected:


public:
    PieceSliding(const PieceColor color, const ChessBoard* board) : Piece(color, board) {};
    [[nodiscard]] virtual std::vector<Vector2i> getMoveDirections() const = 0;
    [[nodiscard]] std::vector<ChessMove> availableMoves(Vector2i position) const override;
};



#endif //SLIDINGPIECE_H

