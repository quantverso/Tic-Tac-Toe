#include "Sprite.h"
#include "Entity.h"
#include "Texture.h"
#include "Color.h"

//--------------------------------------------------------------------------------------------------

Sprite::Sprite(Entity* entity) :
	Component{ entity }
{
}

//--------------------------------------------------------------------------------------------------

void Sprite::SetColor(Color color)
{
	if (m_Texture)
		m_Texture->SetColor(color);
}

//--------------------------------------------------------------------------------------------------

void Sprite::SetTexture(Texture* texture)
{
	if (m_Texture.get() != texture)
		m_Texture = std::shared_ptr<Texture>(texture, [](Texture*) {});
		Rect::operator=(m_Texture->GetRect());
		entity->transform.SetSize(w, h);
}

//--------------------------------------------------------------------------------------------------

void Sprite::SetTexture(const char* file)
{
	m_Texture = std::make_shared<Texture>(file);
	SetTexture(m_Texture.get());
}

//--------------------------------------------------------------------------------------------------

void Sprite::SetRect(Rect rect)
{
	Rect::operator=(rect);
}

//--------------------------------------------------------------------------------------------------
