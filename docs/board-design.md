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

## Method Reference

### `void clearBoard();`

**Purpose**
- Reset the board to a clean empty position.

**What it updates**
- Zeroes all piece bitboards: `pieces[color][pieceType]`
- Zeroes all occupancy bitboards: `occupancy[White]`, `occupancy[Black]`, `occupancy[Both]`
- Sets every square in `pieceOn[64]` to `NoPiece`
- Sets `kingSquare[White]` and `kingSquare[Black]` to `NoSquare`
- Resets game-state fields (side to move, en passant, castling, clocks, zobrist)

**Why it matters**
- Provides a known-valid baseline before loading FEN, tests, or setting custom positions.

---

### `void updateOccupancy();`

**Purpose**
- Rebuild occupancy bitboards from piece bitboards.

**What it does**
- Recomputes `occupancy[White]` by OR-ing all white piece-type bitboards
- Recomputes `occupancy[Black]` by OR-ing all black piece-type bitboards
- Sets `occupancy[Both] = occupancy[White] | occupancy[Black]`

**Why it matters**
- Keeps occupancy in sync after bulk edits (for example, after FEN loading or manual setup).

---

### `void setPiece(Square sq, Piece piece);`

**Purpose**
- Place one piece on one empty square.

**Expected inputs**
- `sq` must be a real square (not `NoSquare`)
- `piece` must be a real piece (not `NoPiece`)
- Target square should currently be empty (`pieceOn[sq] == NoPiece`)

**What it updates**
- `pieceOn[sq]`
- `pieces[color][pieceType]` (sets bit)
- `occupancy[color]` and `occupancy[Both]` (sets bit)
- `kingSquare[color]` if the piece is a king

**Design note**
- This is a low-level board mutation primitive. It does not enforce move legality.

---

### `void removePiece(Square sq);`

**Purpose**
- Remove whatever piece is currently on a square.

**Expected inputs**
- `sq` should be a real square
- If square is empty, function safely returns

**What it updates**
- Clears bit from `pieces[color][pieceType]`
- Clears bit from `occupancy[color]` and `occupancy[Both]`
- Sets `pieceOn[sq] = NoPiece`
- If removing king, sets `kingSquare[color] = NoSquare`

**Design note**
- Generic removal primitive; game rules should prevent illegal king-capture positions elsewhere.

---

### `void movePiece(Square from, Square to);`

**Purpose**
- Move a piece from one square to another using existing primitives.

**Expected inputs**
- `from` and `to` must be real squares
- `from != to`
- `from` should contain a piece

**What it does**
- Reads moving piece from `pieceOn[from]`
- If destination occupied, removes destination piece (capture)
- Removes moving piece from `from`
- Sets moving piece on `to`

**Why this design is good**
- Reuses `removePiece` and `setPiece` so board-state updates stay consistent in one place.

---

### `bool isSquareOccupied(Square sq) const;`

**Purpose**
- Fast read-only query: "is there any piece on this square?"

**What it returns**
- `true` if `pieceOn[sq] != NoPiece`
- `false` otherwise

**Const meaning**
- Marked `const`, so it cannot modify board state.

---

### `Piece pieceAt(Square sq) const;`

**Purpose**
- Fast read-only query: "which exact piece is on this square?"

**What it returns**
- The `Piece` enum at `pieceOn[sq]`
- Returns `NoPiece` for empty squares

**Const meaning**
- Read-only accessor; safe to call on `const Board&`.
