#include "board.h"
#include <algorithm>

void Board::clearBoard() {
    // Board fields
    std::fill(&pieces[0][0], &pieces[0][0] + (kColorCount * kPieceTypeCount), 0ULL);
    std::fill(&occupancy[0], &occupancy[0] + 3, 0ULL);
    std::fill(pieceOn, pieceOn + kSquareCount, NoPiece);
    std::fill(kingSquare, kingSquare + kColorCount, NoSquare);

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