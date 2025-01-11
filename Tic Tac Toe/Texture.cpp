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

	if (texture = IMG_LoadTexture(Engine::window.renderer, file))
	{
		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		size.width = float(w);
		size.height = float(h);
	}
	else
		std::cerr << "Falha ao carregar textura: " << IMG_GetError() << std::endl;
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
