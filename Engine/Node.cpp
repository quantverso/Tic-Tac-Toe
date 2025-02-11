#include "Node.h"
#include "EightPuzzle.h"
#include <algorithm>
#include <cmath>

//--------------------------------------------------------------------------------------------------

Node::Node(size_t size) :
    data{},
    size{ size },
    columns{ int(std::sqrt(size)) },
    indexOfZero{},
    distance{},
    parent{}
{
}

//--------------------------------------------------------------------------------------------------

void Node::Move(size_t index)
{
    int offset{ int(index) - int(indexOfZero) };

    if ((offset == -1 && indexOfZero % columns == 0) ||
        (offset == 1 && indexOfZero % columns == columns - 1))
        return;

    if (abs(offset) == 1 || abs(offset) == columns)
    {
        int temp{ (*this)[indexOfZero] };
        (*this)[indexOfZero] = unsigned((*this)[index]);
        (*this)[index] = temp;
    }
}

//--------------------------------------------------------------------------------------------------

void Node::GetAdjacent(std::vector<NodePtr>& adjacent)
{
    adjacent.clear();
    for (int offset{ -columns }; offset <= columns; offset += columns - 1)
    {
        // Calcula o índice de um nó adjacente
        size_t adjacentIndex{ indexOfZero + offset };
        if (adjacentIndex >= size)
            continue;

        // Guarda o índice atual do elemento 0
        size_t oldIndexOfZero{ indexOfZero };

        // Move elemento para gerar um nó adjacente
        Move(adjacentIndex);

        if (indexOfZero != oldIndexOfZero)
        {
            // Instancia nó vizinho
            NodePtr neighbour{ std::make_shared<Node>(*this) };

            // Restaura o estado do nó
            Move(oldIndexOfZero);

            if (neighbour->GetStatus() == Unvisited)
                adjacent.push_back(neighbour);
        }
    }
}

//--------------------------------------------------------------------------------------------------
