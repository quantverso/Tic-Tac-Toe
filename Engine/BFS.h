#ifndef QUANTVERSO_BFS_H
#define QUANTVERSO_BFS_H

//--------------------------------------------------------------------------------------------------

#include "Pathfinder.h"
#include <queue>

//--------------------------------------------------------------------------------------------------

class BFS : public Pathfinder
{
public:
	BFS(Node& root);

	void Search(std::stack<NodePtr>& solution);

private:
	std::queue<NodePtr> queue;
};

//--------------------------------------------------------------------------------------------------

#endif
