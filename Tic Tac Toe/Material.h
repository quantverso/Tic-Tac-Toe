#ifndef QUANTVERSO_MATERIAL_H
#define QUANTVERSO_MATERIAL_H

//--------------------------------------------------------------------------------------------------

#include "Component.h"
#include <memory>

class Texture;
class Color;

//--------------------------------------------------------------------------------------------------

class Material : public Component, Rect
{
public:
	Material(Entity* entity);

	void Add(const Texture* texture);
	void Add(const char* file);
	void Rect(::Rect rect);
	void Color(::Color color);

	const ::Texture* Texture();

private:
	friend class Entity;

	std::shared_ptr<::Texture> texture;
};

//--------------------------------------------------------------------------------------------------

inline const ::Texture* Material::Texture()
{
	return texture.get();
}

//--------------------------------------------------------------------------------------------------

#endif

