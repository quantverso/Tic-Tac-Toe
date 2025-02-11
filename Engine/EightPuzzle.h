#ifndef QUANTVERSO_EIGHTPUZZLE_H
#define QUANTVERSO_EIGHTPUZZLE_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
#include "Node.h"
#include <array>
#include <stack>

class Pathfinder;

//--------------------------------------------------------------------------------------------------

class EightPuzzle : public Scene
{
public:
	EightPuzzle();

	void Start() override;
	void Update() override;
	void Shuffle();

private:
	friend class Tile;

	const float			borderSize;
	Node				tiles;
	Pathfinder*		    pathfinder;
	std::stack<NodePtr> solution;
};

//--------------------------------------------------------------------------------------------------

#endif
