#include "Texture.h"
#include "Engine.h"
#include "Color.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

Texture::Texture() :
	texture{}
{
}

//--------------------------------------------------------------------------------------------------

Texture::Texture(const char* file) :
	texture{}
{
	Load(file);
}

//--------------------------------------------------------------------------------------------------

Texture::~Texture()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

//--------------------------------------------------------------------------------------------------

void Texture::Load(const char* file)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	texture = IMG_LoadTexture(Engine::window.renderer, file);
	if (!texture)
	{
		std::cerr << "Falha ao carregar textura: " << IMG_GetError() << std::endl;
		return;
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	size.width = float(w);
	size.height = float(h);
}

//--------------------------------------------------------------------------------------------------

void Texture::Color(::Color color)
{
	SDL_SetTextureColorMod(
		texture,
		color.r,
		color.g,
		color.b
	);
}

//--------------------------------------------------------------------------------------------------
