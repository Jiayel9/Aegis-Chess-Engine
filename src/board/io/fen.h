#pragma once

#include <string>
#include<string_view>

# include "../board.h"
// Full FEN into board state
bool loadFEN(Board& board, std::string_view fen);

//Current board state to a FEN string
std::string toFEN(const Board& board);