#include "board.h"
#include <algorithm>
#include <cassert>

void Board::clearBoard() {
    // Board fields
    std::fill(&pieces[0][0], &pieces[0][0] + (kSideCount * kPieceTypeCount), 0ULL);
    std::fill(&occupancy[0], &occupancy[0] + kOccupancyCount, 0ULL);
    std::fill(pieceOn, pieceOn + kSquareCount, NoPiece);
    std::fill(kingSquare, kingSquare + kSideCount, NoSquare);

    // Game-state fields
    sideToMove = White; 
    enPassantSquare = NoSquare; 
    castlingRights = 0;
    halfmoveClock = 0;
    fullmoveNumber = 1; 
    zobristKey = 0ULL; 
}

// Rebuild occupancy bitboards from piece bitboards.
// Useful after bulk edits (e.g. FEN load) to restore consistency.
void Board::updateOccupancy() {
    occupancy[White] = 0ULL;
    occupancy[Black] = 0ULL;

    for (int pieceType = 0; pieceType < kPieceTypeCount; ++pieceType) {
        occupancy[White] |= pieces[White][pieceType];
        occupancy[Black] |= pieces[Black][pieceType];
    }

    occupancy[Both] = occupancy[White] | occupancy[Black];
}
void Board::setPiece(Square sq, Piece piece) {
    // Piece being put must be non-null. Target square must be null
    if (sq == NoSquare || piece == NoPiece) return;
    assert(pieceOn[sq] == NoPiece);

    pieceOn[sq] = piece;
    
    // Extracting information from sq and piece
    const Bitboard mask = 1ULL << sq;
    const Color color = colorOf(piece);
    const PieceType pieceType = typeOf(piece);

    // Setting the piece
    pieces[color][pieceType] |= mask;
    occupancy[color] |= mask;
    occupancy[Both] |= mask;
    if (pieceType == King) {
        kingSquare[color] = sq;
    }
}

void Board::removePiece(Square sq) {
    if (sq == NoSquare) return;

    const Piece piece = pieceOn[sq];
    if (piece == NoPiece) return;

    const Bitboard mask = 1ULL << sq;
    const Color color = colorOf(piece);
    const PieceType pieceType = typeOf(piece);

    // Clear the square in piecesOn and related bitboards
    pieces[color][pieceType] &= ~mask;
    occupancy[color] &= ~mask;
    occupancy[Both] &= ~mask;
    pieceOn[sq] = NoPiece;

    if (pieceType == King) {
        kingSquare[color] = NoSquare;
    }
}

void Board::movePiece(Square from, Square to) {
    assert(from != NoSquare && to != NoSquare);
    assert(from != to);

    const Piece moving = pieceOn[from];
    assert(moving != NoPiece);
    if (moving == NoPiece) return;

    // Capture
    if (pieceOn[to] != NoPiece) {
        removePiece(to);
    }
    
    removePiece(from);
    setPiece(to, moving);
}
bool Board::isSquareOccupied(Square sq) const {
    assert(sq != NoSquare);
    return pieceOn[sq] != NoPiece;
}
Piece Board::pieceAt(Square sq) const {
    assert(sq != NoSquare);
    return pieceOn[sq];
}