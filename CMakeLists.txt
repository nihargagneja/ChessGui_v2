cmake_minimum_required(VERSION 3.29)
project(ChessGUI_v2)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(/opt/homebrew/Cellar/raylib/5.0/include)
link_directories(/opt/homebrew/Cellar/raylib/5.0/lib)

add_executable(ChessGUI_v2
        src/main.cpp
        src/ChessGame.cpp
        src/ChessGame.h
        src/ChessBoard.cpp
        src/ChessBoard.h
        src/ChessPieces/Piece.cpp
        src/ChessPieces/Piece.h
        src/ChessMove.h
        src/ChessPieces/PieceSliding.cpp
        src/ChessPieces/PieceSliding.h
        src/Vector2i.h
        src/ChessPieces/PieceBishop.cpp
        src/ChessPieces/PieceBishop.h
        src/ChessPieces/PieceRook.cpp
        src/ChessPieces/PieceRook.h
        src/ChessPieces/PieceQueen.cpp
        src/ChessPieces/PieceQueen.h
        src/ChessPieces/PieceKnight.cpp
        src/ChessPieces/PieceKnight.h
        src/ChessPieces/PiecePawn.cpp
        src/ChessPieces/PiecePawn.h
        src/ChessPieces/PieceKing.cpp
        src/ChessPieces/PieceKing.h
        src/GUIState.h
)
target_link_libraries(ChessGUI_v2 raylib)

# Required on macOS to link some specific frameworks
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
            "-framework CoreVideo"
            "-framework IOKit"
            "-framework Cocoa"
            "-framework GLUT"
            "-framework OpenGL"
    )
endif()



