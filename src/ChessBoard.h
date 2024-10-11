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

    // does NOT check whether these moves ar legal (i.e. king is checked after making move or not)
    [[nodiscard]] std::vector<ChessMove> getMovesOfAllPieces(std::optional<PieceColor> color) const;

public:
    // DEEP COPIES
    ChessBoard() = default;
    ChessBoard(const ChessBoard &other);
    ChessBoard& operator=(const ChessBoard &other);

    // QUERIES
    [[nodiscard]] static bool inBounds(Vector2i position);

    // QUERYING PIECES AND POSITIONS OF PIECES
    [[nodiscard]] bool pieceExistsAt(Vector2i position) const;
    [[nodiscard]] bool pieceExistsAt(int x, int y) const;
    [[nodiscard]] std::shared_ptr<Piece> getPieceAt(Vector2i position) const;
    [[nodiscard]] std::shared_ptr<Piece> getPieceAt(int x, int y) const;
    [[nodiscard]] std::shared_ptr<Piece> getPieceByID(int id) const;
    [[nodiscard]] Vector2i getPiecePositionByID(int id) const;
    [[nodiscard]] std::vector<Vector2i> getPositionsOf(PieceType pieceType, PieceColor pieceColor) const;

    // QUERYING CHECKS AND MOVE LEGALITY
    [[nodiscard]] bool moveWillCheckKing(const ChessMove &move, PieceColor kingColor) const;
    [[nodiscard]] bool kingIsChecked(PieceColor kingColor) const;

    void printToConsole(const std::string& header) const;
    void executeMove(const ChessMove& move); // should be made private probably
    std::vector<ChessMove> legalMovesAvailableTo(const std::shared_ptr<Piece>& piece) const;

    void draw(const std::shared_ptr<Piece>& selectedPiece) const;
    void setUp();
    void generateRandomConfiguration();
};

#endif //CHESSBOARD_H
