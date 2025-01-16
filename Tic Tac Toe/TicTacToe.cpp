#include "TicTacToe.h"
#include "Minimax.h"
#include "MCTS.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

TicTacToe::TicTacToe() :
    board{},
    size{ GetViewport().w },
    step{}
{
}

//--------------------------------------------------------------------------------------------------

void TicTacToe::Start()
{
    const int border{ int(size * 0.1f) };

    // Define subjanela
    SetViewport(border, border, size - border * 2, size - border * 2);

    step = size / 3;
}

//--------------------------------------------------------------------------------------------------

void TicTacToe::Update()
{
    if (Keyboard::KeyDown(Keyboard::Home))
        board = Board{};

    if (board.CheckWinner() == Player::None)
    {
        if (Mouse::ButtonDown(Mouse::Left))
        {
            auto& mouse{ Mouse::Position(GetViewport()) };

            if (mouse.isInViewport)
            {
                auto& cell{ board[mouse.position.y / step][mouse.position.x / step] };

                if (cell == Player::None)
                {
                    cell = Player::X;

                    //Minimax::Search(board);

                    MCTS::Search(board, 1000, 1 / std::sqrtf(2));
                }
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void TicTacToe::Draw()
{
    Scene::Draw();

    // Configura a cor de renderização
    window.SetRenderDrawColor(Color::White);

    // Dois terços da janela da cena
    static const int twoSteps{ 2 * step };

    // Desenha as linhas verticais
    window.DrawLine(step, 0, step, size);
    window.DrawLine(twoSteps, 0, twoSteps, size);

    // Desenha as linhas horizontais
    window.DrawLine(0, step, size, step);
    window.DrawLine(0, twoSteps, size, twoSteps);

    // Desenha X e O
    for (int row{}; row < 3; ++row)
    {
        for (int col{}; col < 3; ++col)
        {
            static int halfStep{ step / 2 };
            if (board[row][col] == Player::X)
            {
                playerX.Position(col * step + halfStep, row * step + halfStep);
                playerX.Draw();
            }
            else if (board[row][col] == Player::O)
            {
                playerO.Position(col * step + halfStep, row * step + halfStep);
                playerO.Draw();
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
