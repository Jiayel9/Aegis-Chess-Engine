# Board Design

## Syntax

- `using` is C++ alias syntax.

## enum over enum class

- `enum` is more practical here; `enum class` is safer but requires casts for indexing.
  - `enum`: `array[White]`
  - `enum class`: `array[static_cast<int>(Color::White)]`

## Board Struct

What does our board contain?

- Piece bitboards - `pieces[2][6]`
  - Piece locations as bitboards, indexed by `[color][pieceType]`
- Occupancy bitboards `occupancy[3]`
  - Occupied squares for White, Black, and Both
- Direct square lookup - `pieceOn[64]`
  - Exact `Piece` on each square
- King locations - `kingSquare[2]`
- Side to move - `sideToMove`
- Castling rights - `castlingRights`
- En passant target - `enPassantSquare`
  - One square or `NoSquare`
- Halfmove clock - `halfmoveClock`
- Fullmove number - `fullmoveNumber`
- Zobrist hash - `zobristKey`
- Reset function - `clearBoard()`

# Square or Bitboard?

- Use a Square when looking for one exact piece/coordinate
- Use a Bitboard when looking for a set of pieces/coordinates

# Board Methods

What makes sense for our Board to have?
void clearBoard();
void updateOccupancy();
void setPiece(Square sq, Piece piece);
void removePiece(Square sq);
void movePiece(Square from, Square to);
bool isSquareOccupied(Square sq) const;
Piece pieceAt(Square sq) const; (optional but nice)
