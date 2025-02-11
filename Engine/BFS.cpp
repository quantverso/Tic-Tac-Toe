#include "BFS.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

BFS::BFS(Node& root) : Pathfinder(root)
{
	queue.push(this->root); // Coloca o nó raiz na fila
}

//--------------------------------------------------------------------------------------------------

void BFS::Search(std::stack<NodePtr>& solution)
{
	while (!queue.empty())
	{
		auto current{ queue.front() };
		queue.pop();

		if (*current == *target)
		{
			std::cout << "Solucao encontrada na profundidade: " << current->GetDistance() << std::endl
				<< "Nos visitados: " << Node::VisitedNodes() << "\n\n";
			GetPath(solution, current);
			return;
		}

		// Acessa os nós adjacentes
		current->GetAdjacent(adjacent);

		// Visita nós adjacentes, atualiza e coloca na fila
		for (auto& adj : adjacent)
		{
			adj->SetStatus(Node::Visited);
			adj->SetDistance(current->GetDistance() + 1);
			adj->SetParent(current);

			queue.push(adj);
		}	
	}
}

//--------------------------------------------------------------------------------------------------
