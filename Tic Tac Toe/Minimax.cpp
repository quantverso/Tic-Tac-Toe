#include "Minimax.h"
#include <limits>

//--------------------------------------------------------------------------------------------------

void Minimax::Search(Board& board)
{
    auto result{ Value(board, 0, true) };
    if (result.second)
        *result.second = Player::O;
}

//--------------------------------------------------------------------------------------------------

std::pair<int, Player*> Minimax::Value(Board& board, int depth, bool isMaximizing)
{
    // Se há vencedor (estado terminal), retorna utilidade
    if (Player winner{ board.CheckWinner() }; winner == Player::O)
        return { 10 - depth, nullptr };
    else if (winner == Player::X)
        return { depth - 10, nullptr };

    // Obtém movimentos válidos
    std::vector<Player*> moves;
    board.GetAvailableMoves(moves);

    // Se há empate (estado terminal), retorna utilidade
    if (moves.empty())
        return { 0, nullptr };

    int bestValue{ isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max() };
    Player* bestMove;

    for (auto& move : moves)
    {
        // Faz a jogada
        *move = isMaximizing ? Player::O : Player::X;

        // Calcula valor recursivamente com a profundidade aumentada
        auto [value, _] { Value(board, depth + 1, !isMaximizing) };

        // Restaura o tabuleiro
        *move = Player::None;

        // Atualiza melhor valor e movimento
        if ((isMaximizing && value > bestValue) || (!isMaximizing && value < bestValue))
        {
            bestValue = value;
            bestMove = move;
        }
    }

    return { bestValue, bestMove };
}

//--------------------------------------------------------------------------------------------------
