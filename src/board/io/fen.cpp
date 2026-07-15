#include "fen.h"

#include <array>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

// -------------- Internal helpers (private to this translation unit)


namespace {
 
    bool splitFenFields(std::string_view fen, std::array<std::string_view, 6>& out) {
        size_t start = 0;
        int field = 0;
        
        while (field < 6) {
            while (start < fen.size() && fen[start] == ' ') ++start;
            if (start >= fen.size()) return false;

            size_t end = start;
            while (end < fen.size() && fen[end] != ' ') ++end;
            
            out[field++] = fen.substr(start, end - start);
            start = end;
        }
        // Reject extra content
        while (start < fen.size()) {
            if (fen[start] != ' ') return false;
            ++start;
        }
        return true;
    }

    Piece pieceFromFenChar(char c) {
        switch (c) {
            case 'P': return WhitePawn;
            case 'N': return WhiteKnight;
            case 'B': return WhiteBishop;
            case 'R': return WhiteRook;
            case 'Q': return WhiteQueen;
            case 'K': return WhiteKing;
            case 'p': return BlackPawn;
            case 'n': return BlackKnight;
            case 'b': return BlackBishop;
            case 'r': return BlackRook;
            case 'q': return BlackQueen;
            case 'k': return BlackKing;
            default:  return NoPiece;
        }
    }
    
} // namespace