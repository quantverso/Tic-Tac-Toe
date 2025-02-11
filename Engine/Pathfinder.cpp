#include "Pathfinder.h"
#include <numeric>

//--------------------------------------------------------------------------------------------------

Pathfinder::Pathfinder(Node& root) :
	root{ std::make_shared<Node>(root) },
	target{ std::make_shared<Node>(root.Size()) }
{
	for (unsigned i{}; i < target->Size(); ++i)
		(*target)[i] = i;
}

//--------------------------------------------------------------------------------------------------

Pathfinder::~Pathfinder()
{
	Node::Reset();
}

//--------------------------------------------------------------------------------------------------

void Pathfinder::GetPath(std::stack<NodePtr>& solution, NodePtr target)
{
	while (target)
	{
		solution.push(target);
		target = target->GetParent();
	}
}

//--------------------------------------------------------------------------------------------------
