#include "Node.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

std::mt19937 Node::mt{ std::random_device{}() };

//--------------------------------------------------------------------------------------------------

Node::Node(const Board& board, Player nextPlayer, Node* parent) :
	board{ board },
	nextPlayer{ nextPlayer },
	parent{ parent },
	isTerminal{ board.CheckWinner() != Player::None },
	visits{},
	score{}	
{
	if (!isTerminal)
	{
		this->board.GetAvailableMoves(unexploredMoves);
		isTerminal = unexploredMoves.empty();
	}
}

//--------------------------------------------------------------------------------------------------

Node* Node::Select(float explorationConstant)
{
	// Caso haja movimentos não explorados
	if (!unexploredMoves.empty())
	{
		// Faz jogada no tabuleiro para gerar nó sucessor
		auto move{ unexploredMoves.back() };
		unexploredMoves.pop_back();
		*move = nextPlayer;

		// Instacia o nó sucessor
		adjacent.emplace_back(std::make_unique<Node>(board, Player(-nextPlayer), this));

		// Restaura o estado original do tabuleiro
		*move = Player::None;

		// Retorna o nó sucessor
		return adjacent.back().get();
	}

	// Se o nó não for terminal retorna um sucessor com base no UCB1
	if (!isTerminal)
	{
		float bestValue{ -std::numeric_limits<float>::infinity() };
		std::vector<Node*> bestAdjacent;

		// Seleciona os nós mais promissores usando UCB1
		for (auto& adj : adjacent)
		{
			// Calcula o score da perspectiva do jogador atual
			float adjScore{ nextPlayer == Player::O ? adj->score : -adj->score };

			// Calcula o UCB1
			const float exploitation{ adjScore / adj->visits };
			const float exploration{ explorationConstant * std::sqrtf(std::logf(float(visits)) / adj->visits) };
			const float ucbValue{ exploitation + exploration };

			// Se o valor encontrado for melhor que o anterior, reseta o vetor
			if (ucbValue > bestValue)
			{
				bestAdjacent.clear();
				bestValue = ucbValue;
			}

			// Adiciona o nó promissor ao vetor
			if (std::fabs(ucbValue - bestValue) < 1e-6f)
				bestAdjacent.push_back(adj.get());
		}

		// Retorna um dos sucessores mais promissores
		std::uniform_int_distribution<size_t> dist{ 0, bestAdjacent.size() - 1 };
		return bestAdjacent[dist(mt)];
	}

	return this;
}

//--------------------------------------------------------------------------------------------------

float Node::Rollout() const
{
	Player winner{};

	// Verifica se o nó é terminal
	if (isTerminal)
		winner = board.CheckWinner();
	else
	{
		// Instancia uma cópia do tabuleiro
		Board board{ this->board };

		// Carrega os movimentos válidos
		std::vector<Player*> moves;
		board.GetAvailableMoves(moves);

		// Embaralha os movimentos
		std::shuffle(moves.begin(), moves.end(), mt);

		// Faz jogadas aleatórias (simulação)
		for (Player player{ this->nextPlayer }; auto& move : moves)
		{
			*move = player;

			// Verifica se há vencedor após cada jogada
			if (winner = board.CheckWinner(); winner != None)
				break;

			// Alterna o jogador
			player = Player(-player);
		}
	}

	// Retorna o resultado da perspectiva da IA (Player::O)
	return winner == Player::O ? 1.f : winner == Player::X ? -1.f : 0.f;
}

//--------------------------------------------------------------------------------------------------

void Node::Backpropagate(float score)
{
	Node* node{ this };
	while (node != nullptr)
	{
		node->visits++;
		node->score += score;
		node = node->parent;
	}
}

//--------------------------------------------------------------------------------------------------
