//
// Created by Nihar Gagneja on 9/30/24.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <memory>

#include "ChessPieces/Piece.h"


class ChessBoard {
private:
    std::shared_ptr<Piece> m_pieces[8][8];
    std::vector<std::shared_ptr<Piece>> m_capturedPieces = {};

    // does NOT check whether king is checked or not
    // that logic is handled in getAllLegalMovesOnBoard()
    [[nodiscard]] std::vector<ChessMove> getMovesOfAllPieces() const;

public:
    [[nodiscard]] bool pieceExistsAt(Vector2i position) const;
    [[nodiscard]] bool pieceExistsAt(int x, int y) const;
    [[nodiscard]] Piece* getPieceAt(Vector2i position) const;
    [[nodiscard]] Piece* getPieceAt(int x, int y) const;
    [[nodiscard]] Piece* getPieceByID(int id) const;
    [[nodiscard]] Vector2i getPiecePositionByID(int id) const;

    [[nodiscard]] std::vector<Vector2i> getPositionsOf(PieceType pieceType, PieceColor pieceColor) const;

    [[nodiscard]] static bool inBounds(Vector2i position);
    [[nodiscard]] bool moveWillCheckKing(const ChessMove &move, PieceColor kingColor) const;
    [[nodiscard]] bool kingIsChecked(PieceColor kingColor) const;
    [[nodiscard]] std::vector<ChessMove> getAllLegalMovesOnBoard();
    void executeMove(const ChessMove& move);

    void draw(const Piece *selectedPiece) const;
    void setUp();
    void generateRandomConfiguration();
};



#endif //CHESSBOARD_H
