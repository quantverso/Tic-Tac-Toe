#ifndef QUANTVERSO_BOARD_H
#define QUANTVERSO_BOARD_H

//--------------------------------------------------------------------------------------------------

#include <array>
#include <vector>

//--------------------------------------------------------------------------------------------------

enum Player
{
    None,
    O,
    X = -1,
};

class Board
{
public:
    Player CheckWinner() const;
    void GetAvailableMoves(std::vector<Player*>& moves);

private:
    using BoardArray = std::array<std::array<Player, 3>, 3>;

    class Reference
    {
    public:
        Reference(BoardArray& board, size_t index) :
            board{ board },
            firstIndex{ index }
        {
        }

        Player& operator[](size_t secondIndex) const
        {
            return board[firstIndex][secondIndex];
        }

    private:
        BoardArray& board;
        size_t      firstIndex;
    };

    BoardArray board;

public:
    const Reference operator[](size_t index)
    {
        return Reference(board, index);
    }
};

//--------------------------------------------------------------------------------------------------

#endif
