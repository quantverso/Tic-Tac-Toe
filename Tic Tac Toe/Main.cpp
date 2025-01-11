#include "Engine.h"
#include "TicTacToe.h"

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.Size(600, 600);
    Engine::window.Title("Tic Tac Toe");
    Engine::Run(new TicTacToe);

    return 0;
}

//--------------------------------------------------------------------------------------------------
