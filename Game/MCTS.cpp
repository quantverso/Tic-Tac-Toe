#include "MCTS.h"
#include "Board.h"
#include "Node.h"

//--------------------------------------------------------------------------------------------------

void MCTS::Search(Board& board, int iterations, float explorationConstant)
{
    Node root{ board, Player::O, nullptr };

    for (int i{}; i < iterations; ++i)
    {
        Node* node{ &root };

        while (!node->IsTerminal())
        {
            node = node->Select(explorationConstant);
            if (node->Visits() == 0)
                break;
        }

        float score{ node->Rollout() };
        node->Backpropagate(score);
    }

    Node* selected{ root.Select(0.f) };
    selected->GetBoard(board);
}

//--------------------------------------------------------------------------------------------------
