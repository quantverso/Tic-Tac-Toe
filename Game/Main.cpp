#include "Engine.h"
#include "TicTacToe.h"

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.SetSize(600, 600);
    Engine::window.SetTitle("Tic Tac Toe");
    Engine::Run(new TicTacToe);

    return 0;
}

//--------------------------------------------------------------------------------------------------
