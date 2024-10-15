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


    [[nodiscard]] static std::vector<ChessMove> getMovesOfAllPiecesInBoard(const ChessBoard& givenBoard, std::optional<PieceColor> color);

    [[nodiscard]] static bool kingIsCheckedInBoard(const ChessBoard& givenBoard, PieceColor kingColor);

    [[nodiscard]] bool moveIsLegalFor(PieceColor color, const ChessMove & move) const;

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
    [[nodiscard]] std::vector<ChessMove> legalMovesOf(const std::shared_ptr<Piece>& piece) const;


    void printToConsole(const std::string& header) const;
    void executeMove(const ChessMove& move);

    void draw(const std::shared_ptr<Piece>& selectedPiece) const;
    void setUp();

    void initializeBoardFromString(const std::string &str);

    void generateRandomConfiguration();
};

#endif //CHESSBOARD_H
