# Map Of Project

1. Implement Board Representation + Bitboards
   - enums, squares, pieces, occupancies
   - pieceOn[64]
   - kingSquare[2]
   - side to move / castling / en passant / clocks
   - move encoding
   - undo state structure
   - Zobrist keys + full hash rebuild
   - basic attack tables
2. FEN Loading
   - turn a FEN string into a complete Board
   - set bitboards, pieceOn, king squares, state fields, hash
3. Board Printing + Validation
   - print the board clearly
   - verify bitboards, occupancies, pieceOn, king squares, and hash agree
4. Attack Generation
   - pawn attacks
   - knight attacks
   - king attacks
   - bishop / rook / queen attacks with blockers
   - start simple for sliders; optimize later with magic/PEXT tables
5. Pseudo-Legal Move Generation
   - generate moves that follow piece movement rules
   - include captures, pawn pushes, promotions, castling, en passant
   - do not worry about leaving your king in check yet
6. Make / Unmake Moves
   - apply every move type correctly
   - restore every field exactly
   - incrementally update Zobrist hash here
7. Check Detection + Legal Move Filtering
   - determine whether a square is attacked
   - reject pseudo-legal moves that leave your king in check
8. Perft Testing
   - compare legal move counts against known test positions
   - this is your main correctness checkpoint
9. Basic Evaluation
   - material first
   - then piece-square tables, mobility, pawn structure, king safety
10. Search
    - negamax
    - alpha-beta pruning
    - iterative deepening
11. Search Improvements
    - move ordering
    - captures first / MVV-LVA
    - killer moves
    - history heuristic
    - quiescence search
12. Transposition Table
    - use your Zobrist key
    - store searched positions and scores
13. Strength / Performance Work
    - magic bitboards or PEXT sliding attacks
    - better evaluation
    - repetition / draw logic
    - opening book
    - later: NNUE
