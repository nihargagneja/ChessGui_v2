//
// Created by Nihar Gagneja on 9/30/24.
//

// ReSharper disable CppUseStructuredBinding
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

///////////////////////////
//  RETRIEVE PIECES &   //
//  POSITIONS OF PIECES //
//////////////////////////
std::shared_ptr<Piece> ChessBoard::getPieceAt(const Vector2i position) const {
    if(!inBounds(position)) {
        throw std::out_of_range("ChessBoard::getPieceAt");
    }

    return m_pieces[position.x][position.y];
}

std::shared_ptr<Piece> ChessBoard::getPieceAt(const int x, const int y) const {
    return getPieceAt(Vector2i{x, y});
}

std::shared_ptr<Piece> ChessBoard::getPieceByID(const int id) const {
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            auto piece = getPieceAt(Vector2i{x, y});
            if(piece && getPieceAt(x, y)->getID() == id) {
                return getPieceAt(x, y);
            }
        }
    }

    return nullptr;
    //throw std::out_of_range("ChessBoard::getPieceByID");
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
    return Vector2i{-1, -1};
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


///////////////////////////////
//    CHECKS AND GAME LOGIC  //
///////////////////////////////

bool ChessBoard::inBounds(Vector2i position) {
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8;
}

bool ChessBoard::pieceExistsAt(const Vector2i position) const {
    return getPieceAt(position.x, position.y) != nullptr;
}

bool ChessBoard::pieceExistsAt(const int x, const int y) const {
    return pieceExistsAt(Vector2i{x, y});
}

std::vector<ChessMove> ChessBoard::legalMovesOf(const std::shared_ptr<Piece>& piece) const {
    std::vector<ChessMove> legalMoves;

    const auto movesOfPiece = piece->getAvailableMoves();
    for(auto move : movesOfPiece) {
        if (moveIsLegalFor(piece->getColor(), move)) {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}


bool ChessBoard::moveIsLegalFor(const PieceColor color, const ChessMove &move) const {
    ChessBoard boardAfterMove = *this;
    boardAfterMove.executeMove(move);
    boardAfterMove.printToConsole("HEADER");

    if(kingIsCheckedInBoard(boardAfterMove, color)) {
        return false;
    }

    return true;
}

bool ChessBoard::kingIsCheckedInBoard(const ChessBoard& givenBoard, const PieceColor kingColor) {
    const auto locateKingInGivenBoard = givenBoard.getPositionsOf(PieceType::KING, kingColor);
    if(locateKingInGivenBoard.empty()) return false; // protects against crash if no king, though this shouldn't happen in the game

    const auto kingPosition = locateKingInGivenBoard.front();

    std::vector<ChessMove> movesOfAllPieces = getMovesOfAllPiecesInBoard(givenBoard, !kingColor);
    for (const auto& move : movesOfAllPieces) {
        if (move.endPosition == kingPosition && move.moveType == MoveType::CAPTURE) {
            return false;
        }
    }
    return true;
}

std::vector<ChessMove> ChessBoard::getMovesOfAllPiecesInBoard(const ChessBoard& givenBoard, const std::optional<PieceColor> color) {
    std::vector<ChessMove> moves = {};

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            auto piece = givenBoard.getPieceAt(x, y);
            if (piece != nullptr && (color == std::nullopt || piece->getColor() == color.value())) {
                auto availableMovesForPiece = givenBoard.getPieceAt(x, y)->getAvailableMoves();
                moves.insert(
                    moves.end(),
                    availableMovesForPiece.begin(),
                    availableMovesForPiece.end()
                );
            }
        }
    }

    return moves;
}



////////////////////////////////
///         GAME CORE -       //
///  drawing, initialization, //
///   set up, clean up, etc   //
////////////////////////////////
void ChessBoard::setUp() {
    // fill board with null pointers
    for (auto & row : m_pieces) {
        for (auto & piece : row) {
            piece = nullptr;
        }
    }

    m_pieces[0][1] = std::make_shared<PieceRook>    (PieceColor::BLACK_COLOR, this);
    m_pieces[2][2] = std::make_shared<PieceKing>    (PieceColor::WHITE_COLOR, this);


    //
    // // m_pieces[3][3] = std::make_shared<PieceKing>  (PieceColor::WHITE_COLOR, this);
    // // m_pieces[1][1] = std::make_shared<PieceBishop>  (PieceColor::BLACK_COLOR, this);
    //
    // // // BLACK BACK ROW (Fancy Guys)
    // m_pieces[0][0] = std::make_shared<PieceRook>      (PieceColor::BLACK_COLOR, this);
    // m_pieces[1][0] = std::make_shared<PieceKnight>    (PieceColor::BLACK_COLOR, this);
    // m_pieces[2][0] = std::make_shared<PieceBishop>    (PieceColor::BLACK_COLOR, this);
    // m_pieces[3][0] = std::make_shared<PieceQueen>     (PieceColor::BLACK_COLOR, this);
    // // m_pieces[4][0] = std::make_shared<PieceKing>      (PieceColor::BLACK_COLOR, this);
    // m_pieces[5][0] = std::make_shared<PieceBishop>    (PieceColor::BLACK_COLOR, this);
    // m_pieces[6][0] = std::make_shared<PieceKnight>    (PieceColor::BLACK_COLOR, this);
    // m_pieces[7][0] = std::make_shared<PieceRook>      (PieceColor::BLACK_COLOR, this);
    //
    // // BLACK FRONT ROW (Pawns)
    // for (int x = 0; x < 8; x++) {
    //     m_pieces[x][1] = std::make_shared<PiecePawn>  (PieceColor::BLACK_COLOR, this);
    // }
    //
    // // WHITE FRONT ROW (Pawns)
    // for (int x = 0; x < 8; x++) {
    //     m_pieces[x][6] = std::make_shared<PiecePawn>(PieceColor::WHITE_COLOR, this);
    // }
    //
    //
    //
    // // WHITE BACK ROW (Fancy Guys)
    // m_pieces[0][7] = std::make_shared<PieceRook>      (PieceColor::WHITE_COLOR, this);
    // m_pieces[1][7] = std::make_shared<PieceKnight>    (PieceColor::WHITE_COLOR, this);
    // m_pieces[2][7] = std::make_shared<PieceBishop>    (PieceColor::WHITE_COLOR, this);
    // m_pieces[3][7] = std::make_shared<PieceQueen>     (PieceColor::WHITE_COLOR, this);
    // // m_pieces[4][7] = std::make_shared<PieceKing>      (PieceColor::WHITE_COLOR, this);
    // m_pieces[5][7] = std::make_shared<PieceBishop>    (PieceColor::WHITE_COLOR, this);
    // m_pieces[6][7] = std::make_shared<PieceKnight>    (PieceColor::WHITE_COLOR, this);
    // m_pieces[7][7] = std::make_shared<PieceRook>      (PieceColor::WHITE_COLOR, this);
    //
    // m_pieces[4][4] = std::make_shared<PieceBishop>     (PieceColor::BLACK_COLOR, this);
    // m_pieces[3][3] = std::make_shared<PieceKing>      (PieceColor::BLACK_COLOR, this);
    // m_pieces[6][3] = std::make_shared<PieceKing>      (PieceColor::WHITE_COLOR, this);
    //
    // m_pieces[3][6] = nullptr;
    // m_pieces[5][3] = std::make_shared<PiecePawn>(PieceColor::WHITE_COLOR, this);

}


// NOT DONE
void ChessBoard::initializeBoardFromString(const std::string& str) {
    std::string layout =
        "rkbqwbkr\n"
        "pppppppp\n"
        "--------\n"
        "--------\n"
        "--------\n"
        "--------\n"
        "PPPPPPPP\n"
        "RKBQWBKR\n";

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

void  ChessBoard::draw(const std::shared_ptr<Piece>& selectedPiece) const {
    for(int row = 0;row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            // draw tiles
            const Color squareColor = (row + col) % 2 != 0 ? DARKGRAY : WHITE;
            DrawRectangle(col * 100, row * 100, 100, 100, squareColor);

            // draw chess piece if there is one
            if(const auto pieceToDraw = getPieceAt(Vector2i(col, row))) {
                DrawText(pieceToDraw->getSymbol().c_str(), col * 100 + 20, row * 100, 100, BEIGE);
            }
        }
    }



    if(selectedPiece) {
        for(const ChessMove& move : legalMovesOf(selectedPiece)) {
            const Color squareColor = (move.moveType == MoveType::CAPTURE) ? Color(ColorAlpha(RED, 0.4f)) : ColorAlpha(GREEN, 0.4f);
            DrawRectangle(move.endPosition.x * 100, move.endPosition.y * 100, 100, 100, squareColor);
        }
    }

    // if(kingIsChecked(PieceColor::WHITE_COLOR)) {
    //     DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color(255, 0, 0, 50));
    // }
}

// Function is "dumb." It assumes the move it has been provided is valid/legal
void ChessBoard::executeMove(const ChessMove& move) {
    if(move.moveType == MoveType::INTO_EMPTY) {
        m_pieces[move.endPosition.x][move.endPosition.y] = m_pieces[move.startPosition.x][move.startPosition.y];
        m_pieces[move.startPosition.x][move.startPosition.y] = nullptr;
    } else if (move.moveType == MoveType::CAPTURE) {
        m_capturedPieces.push_back(m_pieces[move.endPosition.x][move.endPosition.y]);
        m_pieces[move.endPosition.x][move.endPosition.y] = m_pieces[move.startPosition.x][move.startPosition.y];
        m_pieces[move.startPosition.x][move.startPosition.y] = nullptr;
    } else if (move.moveType == MoveType::CASTLE) {
        // need to implement
    }
}

void ChessBoard::printToConsole(const std::string& header) const {
    std::cout << header << "-------------------------" << std::endl;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0 ; x < 8; ++x) {
            if (m_pieces[x][y]) { std::cout << m_pieces[x][y]->getSymbol(); }
            else { std::cout << '-'; }
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------" << std::endl << std::endl;

}

///////////////////////
///   DEEP COPIES   //
//////////////////////
ChessBoard::ChessBoard(const ChessBoard &other) {
    m_capturedPieces.clear();

    for (auto& pieceColumn : m_pieces) {
        for (auto& piece : pieceColumn) {
            piece = nullptr;
        }
    }

    // deep copy pieces array
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_pieces[i][j] = other.m_pieces[i][j] ? other.m_pieces[i][j]->xerox() : nullptr;
        }
    }

    // deep copy captured pieces
    for (const auto& capturedPiece : other.m_capturedPieces) {
        m_capturedPieces.push_back(capturedPiece ? capturedPiece->xerox() : nullptr);
    }
}

ChessBoard& ChessBoard::operator=(const ChessBoard &other) {
    if (this == &other) return *this; // self-assignment

    for (auto& pieceColumn : m_pieces) {
        for (auto& piece : pieceColumn) {
            piece = nullptr;
        }
    }

    // Clear current state
    m_capturedPieces.clear();

    // Deep copy the pieces array
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            m_pieces[i][j] = (other.m_pieces[i][j]) ? other.m_pieces[i][j]->xerox() : nullptr;
        }
    }

    // Deep copy the captured pieces vector
    for (const auto& capturedPiece : other.m_capturedPieces) {
        m_capturedPieces.push_back(capturedPiece ? capturedPiece->xerox() : nullptr);
    }

    return *this;
}