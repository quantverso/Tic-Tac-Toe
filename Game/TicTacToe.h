#ifndef QUANTVERSO_TICTACTOE_H
#define QUANTVERSO_TICTACTOE_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------

class TicTacToe : public Scene
{
public:
    TicTacToe();

    void Start();
    void Update();
    void Draw();

public:
    class PlayerX
    {
    public:
        void Position(int x, int y) { position = { x, y }; }
        void Draw() const
        {
            window.DrawLine(
                position.x - size, position.y - size,
                position.x + size, position.y + size);

            window.DrawLine(
                position.x + size, position.y - size,
                position.x - size, position.y + size);
        }

    private:
        const unsigned size{ 40 };
        Vector2i       position{};

    } m_PlayerX;

    class PlayerO : Circle
    {
    public:
        using Circle::Position;
        PlayerO() { SetRadius(40); }
        void Draw() const { window.Draw(this); }

    } m_PlayerO;

    Board      m_Board;
    const int& m_Size;
    int        m_Step;
};

//--------------------------------------------------------------------------------------------------

#endif
