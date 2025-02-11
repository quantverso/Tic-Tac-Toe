#ifndef QUANTVERSO_NODE_H
#define QUANTVERSO_NODE_H

//--------------------------------------------------------------------------------------------------

#include "Board.h"
#include <vector>
#include <memory>
#include <random>

//--------------------------------------------------------------------------------------------------

class Node
{
public:
	Node(const Board& board, Player nextPlayer, Node* parent);

	Node* Select(float explorationConstant);
	float Rollout() const;
	void Backpropagate(float score);
	bool IsTerminal() const;
	const int& Visits() const;	
	void GetBoard(Board& board);

private:
	using NodePtr = std::unique_ptr<Node>;

	static std::mt19937	 s_Mt;

	Board				 m_Board;
	const Player		 m_NextPlayer;
	Node*				 m_Parent;
	bool				 m_IsTerminal;
	int					 m_Visits;
	float				 m_Score;
	std::vector<Player*> m_UnexploredMoves;
	std::vector<NodePtr> m_Adjacent;
};

//--------------------------------------------------------------------------------------------------

inline bool Node::IsTerminal() const
{
	return m_IsTerminal;
}

//--------------------------------------------------------------------------------------------------

inline const int& Node::Visits() const
{
	return m_Visits;
}

//--------------------------------------------------------------------------------------------------

inline void Node::GetBoard(Board& board)
{
	board = m_Board;
}

//--------------------------------------------------------------------------------------------------

#endif
