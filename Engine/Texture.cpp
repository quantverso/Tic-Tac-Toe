#include "Texture.h"
#include "Engine.h"
#include "Color.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

Texture::Texture() :
	m_Texture{}
{
}

//--------------------------------------------------------------------------------------------------

Texture::Texture(const char* file) :
	m_Texture{}
{
	Load(file);
}

//--------------------------------------------------------------------------------------------------

Texture::~Texture()
{
	if (m_Texture)
		SDL_DestroyTexture(m_Texture);
}

//--------------------------------------------------------------------------------------------------

void Texture::Load(const char* file)
{
	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

	m_Texture = IMG_LoadTexture(Engine::window.GetRenderer(), file);
	if (!m_Texture)
	{
		std::cerr << "Falha ao carregar textura: " << IMG_GetError() << std::endl;
		return;
	}

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Rect.w, &m_Rect.h);
}

//--------------------------------------------------------------------------------------------------

void Texture::SetColor(Color color)
{
	SDL_SetTextureColorMod(
		m_Texture,
		color.r,
		color.g,
		color.b
	);
}

//--------------------------------------------------------------------------------------------------
