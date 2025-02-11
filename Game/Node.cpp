#include "Node.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

std::mt19937 Node::s_Mt{ std::random_device{}() };

//--------------------------------------------------------------------------------------------------

Node::Node(const Board& board, Player nextPlayer, Node* parent) :
	m_Board{ board },
	m_NextPlayer{ nextPlayer },
	m_Parent{ parent },
	m_IsTerminal{ board.CheckWinner() != Player::None },
	m_Visits{},
	m_Score{}	
{
	if (!m_IsTerminal)
	{
		m_Board.GetAvailableMoves(m_UnexploredMoves);
		m_IsTerminal = m_UnexploredMoves.empty();
	}
}

//--------------------------------------------------------------------------------------------------

Node* Node::Select(float explorationConstant)
{
	// Caso haja movimentos não explorados
	if (!m_UnexploredMoves.empty())
	{
		// Faz jogada no tabuleiro para gerar nó sucessor
		auto move{ m_UnexploredMoves.back() };
		m_UnexploredMoves.pop_back();
		*move = m_NextPlayer;

		// Instacia o nó sucessor
		m_Adjacent.emplace_back(std::make_unique<Node>(m_Board, Player(-m_NextPlayer), this));

		// Restaura o estado original do tabuleiro
		*move = Player::None;

		// Retorna o nó sucessor
		return m_Adjacent.back().get();
	}

	// Se o nó não for terminal retorna um sucessor com base no UCB1
	if (!m_IsTerminal)
	{
		float bestValue{ -std::numeric_limits<float>::infinity() };
		std::vector<Node*> bestAdjacent;

		// Seleciona os nós mais promissores usando UCB1
		for (auto& adj : m_Adjacent)
		{
			// Calcula o score da perspectiva do jogador atual
			float adjScore{ m_NextPlayer == Player::O ? adj->m_Score : -adj->m_Score };

			// Calcula o UCB1
			const float exploitation{ adjScore / adj->m_Visits };
			const float exploration{ explorationConstant * std::sqrtf(std::logf(float(m_Visits)) / adj->m_Visits) };
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
		return bestAdjacent[dist(s_Mt)];
	}

	return this;
}

//--------------------------------------------------------------------------------------------------

float Node::Rollout() const
{
	Player winner{};

	// Verifica se o nó é terminal
	if (m_IsTerminal)
		winner = m_Board.CheckWinner();
	else
	{
		// Instancia uma cópia do tabuleiro
		Board board{ m_Board };

		// Carrega os movimentos válidos
		std::vector<Player*> moves;
		board.GetAvailableMoves(moves);

		// Embaralha os movimentos
		std::shuffle(moves.begin(), moves.end(), s_Mt);

		// Faz jogadas aleatórias (simulação)
		for (Player player{ m_NextPlayer }; auto& move : moves)
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
		node->m_Visits++;
		node->m_Score += score;
		node = node->m_Parent;
	}
}

//--------------------------------------------------------------------------------------------------
