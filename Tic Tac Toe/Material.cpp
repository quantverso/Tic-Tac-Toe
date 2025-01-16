#include "Material.h"
#include "Entity.h"
#include "Texture.h"
#include "Color.h"

//--------------------------------------------------------------------------------------------------

Material::Material(Entity* entity) :
	Component{ entity }
{
}

//--------------------------------------------------------------------------------------------------

void Material::Color(::Color color)
{
	if (texture)
		texture->Color(color);
}

//--------------------------------------------------------------------------------------------------

void Material::Add(const ::Texture* texture)
{
	if (this->texture.get() != texture)
		this->texture = std::shared_ptr<::Texture>(const_cast<::Texture*>(texture), [](::Texture*) {});

	entity->transform.Size(texture->Size().width, texture->Size().height);

	w = int(texture->Size().width);
	h = int(texture->Size().height);
}

//--------------------------------------------------------------------------------------------------

void Material::Add(const char* file)
{
	texture = std::make_shared<::Texture>(file);
	Add(texture.get());
}

//--------------------------------------------------------------------------------------------------

void Material::Rect(::Rect rect)
{
	Rect::operator=(rect);
}

//--------------------------------------------------------------------------------------------------
