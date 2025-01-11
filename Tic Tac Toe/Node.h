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

	static std::mt19937	 mt;

	Board				 board;
	const Player		 nextPlayer;
	Node*				 parent;
	bool				 isTerminal;
	int					 visits;
	float				 score;
	std::vector<Player*> unexploredMoves;
	std::vector<NodePtr> adjacent;
};

//--------------------------------------------------------------------------------------------------

inline bool Node::IsTerminal() const
{
	return isTerminal;
}

//--------------------------------------------------------------------------------------------------

inline const int& Node::Visits() const
{
	return visits;
}

//--------------------------------------------------------------------------------------------------

inline void Node::GetBoard(Board& board)
{
	board = this->board;
}

//--------------------------------------------------------------------------------------------------

#endif
