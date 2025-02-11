#ifndef QUANTVERSO_TILE_H
#define QUANTVERSO_TILE_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

class EightPuzzle;

//--------------------------------------------------------------------------------------------------

class Tile : public Entity
{
public:
	Tile();

	void Awake() override;
	void Update() override;
	void Draw() override;
	
	static const size_t& Clicked();

private:
	inline static float  size;
	inline static size_t clicked;

	const size_t index;
};

//--------------------------------------------------------------------------------------------------

inline const size_t& Tile::Clicked()
{
	return clicked;
}

//--------------------------------------------------------------------------------------------------

#endif
