#include "TicTacToe.h"
#include "Minimax.h"
#include "MCTS.h"
#include <cmath>
#include "Entity.h"

//--------------------------------------------------------------------------------------------------

TicTacToe::TicTacToe() :
    m_Board{},
    m_Size{ GetViewport().w },
    m_Step{}
{
    Texture texture;
}

//--------------------------------------------------------------------------------------------------

void TicTacToe::Start()
{
    const int border{ int(m_Size * 0.1f) };

    // Define subjanela
    SetViewport(border, border, m_Size - border * 2, m_Size - border * 2);

    m_Step = m_Size / 3;
}

//--------------------------------------------------------------------------------------------------

void TicTacToe::Update()
{
    if (Keyboard::IsKeyDown(Keyboard::Home))
        m_Board = Board{};

    if (Mouse::IsButtonDown(Mouse::Left) && m_Board.CheckWinner() == Player::None)
    {
        auto& mouse{ Mouse::GetPosition(GetViewport()) };

        if (mouse.isInViewport)
        {
            Player& cell{ m_Board[mouse.position.y / m_Step][mouse.position.x / m_Step] };

            if (cell == Player::None)
            {
                cell = Player::X;

                //Minimax::Search(m_Board);

                MCTS::Search(m_Board, 1000, std::sqrtf(2));
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
    static const int twoSteps{ 2 * m_Step };

    // Desenha as linhas verticais
    window.DrawLine(m_Step, 0, m_Step, m_Size);
    window.DrawLine(twoSteps, 0, twoSteps, m_Size);

    // Desenha as linhas horizontais
    window.DrawLine(0, m_Step, m_Size, m_Step);
    window.DrawLine(0, twoSteps, m_Size, twoSteps);

    // Desenha X e O
    for (int row{}; row < 3; ++row)
    {
        for (int col{}; col < 3; ++col)
        {
            static int halfStep{ m_Step / 2 };
            if (m_Board[row][col] == Player::X)
            {
                m_PlayerX.Position(col * m_Step + halfStep, row * m_Step + halfStep);
                m_PlayerX.Draw();
            }
            else if (m_Board[row][col] == Player::O)
            {
                m_PlayerO.Position(col * m_Step + halfStep, row * m_Step + halfStep);
                m_PlayerO.Draw();
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
