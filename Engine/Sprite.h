#ifndef QUANTVERSO_SPRITE_H
#define QUANTVERSO_SPRITE_H

//--------------------------------------------------------------------------------------------------

#include "Component.h"
#include <memory>

class Texture;
class Color;

//--------------------------------------------------------------------------------------------------

class Sprite : public Component, Rect
{
public:
	Sprite(Entity* entity);

	void SetTexture(Texture* texture);
	void SetTexture(const char* file);
	void SetRect(Rect rect);
	void SetColor(Color color);

private:
	friend class Entity;

	std::shared_ptr<Texture> m_Texture;
};

//--------------------------------------------------------------------------------------------------

#endif
