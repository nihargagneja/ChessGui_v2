//
// Created by Nihar Gagneja on 9/30/24.
//

#include <raylib.h>
#include "ChessBoard.h"

#include <iostream>
#include <ostream>
#include <vector>

#include "ChessPieces/Piece.h"
#include "ChessPieces/PieceBishop.h"
#include "ChessPieces/PieceKing.h"
#include "ChessPieces/PieceKnight.h"
#include "ChessPieces/PieceQueen.h"
#include "ChessPieces/PieceRook.h"
#include "ChessPieces/PiecePawn.h"


Piece* ChessBoard::getPieceAt(const Vector2i position) const {
    if(!inBounds(position)) {
        throw std::out_of_range("ChessBoard::getPieceAt");
    }

    return m_pieces[position.x][position.y].get();
}


Piece* ChessBoard::getPieceAt(const int x, const int y) const {
    return getPieceAt(Vector2i{x, y});
}

Piece* ChessBoard::getPieceByID(const int id) const {
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            auto piece = getPieceAt(Vector2i{x, y});
            if(piece && getPieceAt(x, y)->getID() == id) {
                return getPieceAt(x, y);
            }
        }
    }

    throw std::out_of_range("ChessBoard::getPieceByID");
}

Vector2i ChessBoard::getPiecePositionByID(const int id) const {
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            auto piece = getPieceAt(Vector2i{x, y});
            if(piece && getPieceAt(x, y)->getID() == id) {
                return Vector2i{x, y};
            }
        }
    }

    throw std::out_of_range("ChessBoard::getPieceByID");
}

std::vector<Vector2i> ChessBoard::getPositionsOf(PieceType pieceType, PieceColor pieceColor) const {
    std::vector<Vector2i> positions;

    for (int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            auto currentPiece = m_pieces[x][y];
            if(currentPiece != nullptr && currentPiece->getPieceType() == PieceType::KING && currentPiece->getColor() == pieceColor) {
                positions.push_back( Vector2i{x, y} );
            }
        }
    }

    return positions;
}

bool ChessBoard::inBounds(Vector2i position) {
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8;
}

bool ChessBoard::moveWillCheckKing(const ChessMove &move, const PieceColor kingColor) const {
    ChessBoard boardAfterMove = *this;

    // check here about shallow copy vs deep copy
    boardAfterMove.executeMove(move);
    if(kingIsChecked(kingColor)) { return true; }
    else { return false; }
}

bool ChessBoard::kingIsChecked(PieceColor kingColor) const {
    bool result = false;

    // find the kings position on the board
    Vector2i kingPos = getPositionsOf(PieceType::KING, kingColor).front();

    // if any ChessMoves on board have a destination
    // at the kings position and are of type CAPTURE
    // then the king is in check
    for(auto move : getMovesOfAllPieces()) {
        if(move.endPosition == kingPos) {
            result = true;
        }
    }

    return result;
}

// this private function does NOT check for if the king cant move there
// because it is in check. That logic is handled by the public function getAllLegalMovesOnBoard
std::vector<ChessMove> ChessBoard::getMovesOfAllPieces() const {
    std::vector<ChessMove> movesOfAllPieces = {};

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            auto piece = getPieceAt(x, y);
            if(piece != nullptr) {
                std::vector<ChessMove> movesOfPiece = piece->availableMoves();
                movesOfAllPieces.insert(
                    movesOfAllPieces.end(),
                    movesOfPiece.begin(),
                    movesOfPiece.end()
                );
            }
        }
    }

    return movesOfAllPieces;
}

bool ChessBoard::pieceExistsAt(Vector2i position) const {
    return getPieceAt(position.x, position.y) != nullptr;
}

bool ChessBoard::pieceExistsAt(int x, int y) const {
    return pieceExistsAt(Vector2i{x, y});
}

std::vector<ChessMove> ChessBoard::getAllLegalMovesOnBoard() {
    return getMovesOfAllPieces();
}

void ChessBoard::executeMove(const ChessMove& move) {
    if(move.type == MoveType::INTO_EMPTY) {
        m_pieces[move.endPosition.x][move.endPosition.y] = m_pieces[move.startPosition.x][move.startPosition.y];
        m_pieces[move.startPosition.x][move.startPosition.y] = nullptr;
    } else if (move.type == MoveType::CAPTURE) {
        m_capturedPieces.push_back(m_pieces[move.endPosition.x][move.endPosition.y]);
        m_pieces[move.endPosition.x][move.endPosition.y] = m_pieces[move.startPosition.x][move.startPosition.y];
        m_pieces[move.startPosition.x][move.startPosition.y] = nullptr;
    } else if (move.type == MoveType::CASTLE) {
        // need to implement
    }
}

void ChessBoard::draw(const Piece *selectedPiece) const {
    for(int row = 0;row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            // draw tiles
            Color squareColor = (row + col) % 2 != 0 ? DARKGRAY : WHITE;
            DrawRectangle(col * 100, row * 100, 100, 100, squareColor);

            // draw chess piece if there is one
            auto pieceToDraw = getPieceAt(Vector2i(col, row));
            if(pieceToDraw != nullptr) {
                DrawText(pieceToDraw->getSymbol().c_str(), col * 100 + 20, row * 100, 100, BEIGE);
            }
        }
    }

    if(selectedPiece != nullptr) {
        for (ChessMove move : selectedPiece->availableMoves()) {
            Color squareColor = (move.type == MoveType::CAPTURE) ? Color(ColorAlpha(RED, 0.4f)) : ColorAlpha(GREEN, 0.4f);
            DrawRectangle(move.endPosition.x * 100, move.endPosition.y * 100, 100, 100, squareColor);
        }
    }
}

void ChessBoard::setUp() {
    // fill board with null pointers
    for (auto & row : m_pieces) {
        for (auto & piece : row) {
            piece = nullptr;
        }
    }

    // // BLACK BACK ROW (Fancy Guys)
    m_pieces[0][0] = std::make_shared<PieceRook>      (PieceColor::BLACK_COLOR, this);
    m_pieces[1][0] = std::make_shared<PieceKnight>    (PieceColor::BLACK_COLOR, this);
    m_pieces[2][0] = std::make_shared<PieceBishop>    (PieceColor::BLACK_COLOR, this);
    m_pieces[3][0] = std::make_shared<PieceQueen>     (PieceColor::BLACK_COLOR, this);
    // m_pieces[4][0] = std::make_shared<PieceKing>      (PieceColor::BLACK_COLOR, this);
    m_pieces[5][0] = std::make_shared<PieceBishop>    (PieceColor::BLACK_COLOR, this);
    m_pieces[6][0] = std::make_shared<PieceKnight>    (PieceColor::BLACK_COLOR, this);
    m_pieces[7][0] = std::make_shared<PieceRook>      (PieceColor::BLACK_COLOR, this);

    // BLACK FRONT ROW (Pawns)
    for (int x = 0; x < 8; x++) {
        m_pieces[x][1] = std::make_shared<PiecePawn>  (PieceColor::BLACK_COLOR, this);
    }

    // WHITE FRONT ROW (Pawns)
    for (int x = 0; x < 8; x++) {
        m_pieces[x][6] = std::make_shared<PiecePawn>(PieceColor::WHITE_COLOR, this);
    }

    // WHITE BACK ROW (Fancy Guys)
    m_pieces[0][7] = std::make_shared<PieceRook>      (PieceColor::WHITE_COLOR, this);
    m_pieces[1][7] = std::make_shared<PieceKnight>    (PieceColor::WHITE_COLOR, this);
    m_pieces[2][7] = std::make_shared<PieceBishop>    (PieceColor::WHITE_COLOR, this);
    m_pieces[3][7] = std::make_shared<PieceQueen>     (PieceColor::WHITE_COLOR, this);
    // m_pieces[4][7] = std::make_shared<PieceKing>      (PieceColor::WHITE_COLOR, this);
    m_pieces[5][7] = std::make_shared<PieceBishop>    (PieceColor::WHITE_COLOR, this);
    m_pieces[6][7] = std::make_shared<PieceKnight>    (PieceColor::WHITE_COLOR, this);
    m_pieces[7][7] = std::make_shared<PieceRook>      (PieceColor::WHITE_COLOR, this);

    m_pieces[4][4] = std::make_shared<PieceBishop>     (PieceColor::BLACK_COLOR, this);
    m_pieces[3][3] = std::make_shared<PieceKing>      (PieceColor::BLACK_COLOR, this);
    m_pieces[6][3] = std::make_shared<PieceKing>      (PieceColor::WHITE_COLOR, this);

}

void ChessBoard::generateRandomConfiguration() {
    for (auto & row : m_pieces) {
        for (auto & piece : row) {
            auto shouldDrawPiece = GetRandomValue(0, 10) < 5;
            auto pieceType = GetRandomValue(0, 5);
            auto pieceColor = GetRandomValue(0, 1);

            if (shouldDrawPiece) {
                switch(pieceType) {
                    case static_cast<int>(PieceType::PAWN):
                        piece = std::make_shared<PiecePawn>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    break;
                    case static_cast<int>(PieceType::KNIGHT):
                        piece = std::make_shared<PieceKnight>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    case static_cast<int>(PieceType::BISHOP):
                        piece = std::make_shared<PieceBishop>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    break;
                    case static_cast<int>(PieceType::KING):
                        piece = std::make_shared<PieceKing>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    break;
                    case static_cast<int>(PieceType::ROOK):
                        piece = std::make_shared<PieceRook>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    break;
                    case static_cast<int>(PieceType::QUEEN):
                        piece = std::make_shared<PieceQueen>(pieceColor == 0 ? PieceColor::WHITE_COLOR : PieceColor::BLACK_COLOR, this);
                    break;
                    default:
                        piece = nullptr;
                    break;
                }
            }
        }
    }
}
