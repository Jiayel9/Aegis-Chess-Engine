#pragma once // Each header is only included once

#include <cstdint>

// Core fixed-width engine types.
using Bitboard = uint64_t;
using Move = uint32_t;

// Compile time counts
constexpr int kSideCount = 2;
constexpr int kOccupancyCount = 3;
constexpr int kPieceTypeCount = 6;
constexpr int kSquareCount = 64;

enum Color { White, Black, Both};
// PieceType index convention:
// Pawn=0, Knight=1, Bishop=2, Rook=3, Queen=4, King=5
enum PieceType { Pawn, Knight, Bishop, Rook, Queen, King};
// Piece index map:
// 0-5  -> White Pieces
// 6-11 -> Black Pieces
// 12   -> NoPiece
enum Piece { 
    WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
    BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
    NoPiece
};

inline Color colorOf(Piece piece) {
    return (piece <= WhiteKing) ? White : Black;
}

inline PieceType typeOf(Piece piece) {
    return static_cast<PieceType>(piece % kPieceTypeCount);
}
// Canonical square-to-index mapping convention (A1 = 0, H8 = 63).
enum Square {
    A1, B1, C1, D1, E1, F1, G1, H1, 
    A2, B2, C2, D2, E2, F2, G2, H2, 
    A3, B3, C3, D3, E3, F3, G3, H3, 
    A4, B4, C4, D4, E4, F4, G4, H4, 
    A5, B5, C5, D5, E5, F5, G5, H5, 
    A6, B6, C6, D6, E6, F6, G6, H6, 
    A7, B7, C7, D7, E7, F7, G7, H7, 
    A8, B8, C8, D8, E8, F8, G8, H8,
    NoSquare
};
enum CastlingRights { 
    WhiteKingside = 1 << 0, // 0001
    WhiteQueenside = 1 << 1, // 0010
    BlackKingside = 1 << 2, // 0100
    BlackQueenside = 1 << 3 // 1000
};
struct Board {
    // Board fields
    Bitboard pieces[kSideCount][kPieceTypeCount]; 
    Bitboard occupancy[kOccupancyCount]; 
    Piece pieceOn[kSquareCount]; 
    Square kingSquare[kSideCount]; 

    // Game-state fields (cannot be derived from pieces on the board alone)
    Color sideToMove; 
    Square enPassantSquare; 
    uint8_t castlingRights;
    int halfmoveClock;
    int fullmoveNumber; 
    uint64_t zobristKey; // Position fingerprint (piece-square + side + castling + en passant).

    void clearBoard();
    void updateOccupancy();
    void setPiece(Square sq, Piece piece);
    void removePiece(Square sq);
    void movePiece(Square from, Square to);
    bool isSquareOccupied(Square sq) const;
    Piece pieceAt(Square sq) const;
};