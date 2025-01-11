#include "Board.h"

//--------------------------------------------------------------------------------------------------

Player Board::CheckWinner() const
{
    auto check{ [](int startRow, int startCol, int rowStep, int colStep, const std::array<std::array<Player, 3>, 3>& board) -> Player
        {
            const Player player{ board[startRow][startCol] };

            if (player == Player::None)
                return Player::None;

            for (int i{}; i < 2; ++i)
            {
                if (board[startRow += rowStep][startCol += colStep] != player)
                    return Player::None;
            }

            return player;
        }
    };

    Player player;

    // Verifica linhas e colunas
    for (int i{}; i < 3; ++i)
    {
        if (player = check(i, 0, 0, 1, board); player != Player::None)
            return player;

        if (player = check(0, i, 1, 0, board); player != Player::None)
            return player;
    }

    // Verifica diagonais
    if (player = check(0, 0, 1, 1, board); player != Player::None)
        return player;

    if (player = check(0, 2, 1, -1, board); player != Player::None)
        return player;

    return Player::None;
}

//--------------------------------------------------------------------------------------------------

void Board::GetAvailableMoves(std::vector<Player*>& moves)
{
    for (auto& row : board)
    {
        for (auto& move : row)
        {
            if (move == Player::None)
                moves.push_back(&move);
        }
    }
}

//--------------------------------------------------------------------------------------------------
