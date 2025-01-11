#ifndef QUANTVERSO_MINIMAX_H
#define QUANTVERSO_MINIMAX_H

//--------------------------------------------------------------------------------------------------

#include "TicTacToe.h"

//--------------------------------------------------------------------------------------------------

class Minimax
{
public:
    static void Search(Board& board);

private:    
    static std::pair<int, Player*> Value(Board& board, int depth, bool isMaximizing);
};

//--------------------------------------------------------------------------------------------------

#endif
