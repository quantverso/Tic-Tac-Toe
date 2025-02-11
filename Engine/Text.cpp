#include "Text.h"
#include "Engine.h"
#include <cstdlib>
#include <iostream>

//--------------------------------------------------------------------------------------------------

Text::Text() :
	m_Size{},
	m_Font{},
	m_Color{}
{
}

//--------------------------------------------------------------------------------------------------

Text::~Text()
{
	if (m_Font)
		TTF_CloseFont(m_Font);
}

//--------------------------------------------------------------------------------------------------

void Text::Load(const char* file, unsigned size)
{
	this->m_Size = size;

	m_Font = TTF_OpenFont(file, size);
	if (!m_Font)
	{
		std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
		return;
	}

	m_Rect.h = size;
	m_Rect.w = size;
}

//--------------------------------------------------------------------------------------------------

void Text::SetString(const std::string& string)
{
	m_Text = string;
	m_Rect.w = int(string.size()) * m_Size;

	m_Surface = TTF_RenderText_Solid(m_Font, string.c_str(), m_Color);
	if (!m_Surface)
	{
		std::cerr << "Erro ao criar superficie de texto: " << TTF_GetError() << std::endl;
		return;
	}

	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

	m_Texture = SDL_CreateTextureFromSurface(Engine::window.GetRenderer(), m_Surface);
	if (!m_Texture)
		std::cerr << "Erro ao criar textura de texto: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(m_Surface);
	m_Surface = nullptr;
}

//--------------------------------------------------------------------------------------------------

void Text::Position(int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
}

//--------------------------------------------------------------------------------------------------

void Text::SetSize(int w, int h)
{
	m_Size = w;
	m_Rect.w = w;
	m_Rect.h = h;
}

//--------------------------------------------------------------------------------------------------

void Text::SetSize(float w, float h)
{
	SetSize(int(w), int(h));
}

//--------------------------------------------------------------------------------------------------

void Text::SetColor(Color color)
{
	m_Color = color;
	if (!m_Text.empty())
		SetString(m_Text);
}

//--------------------------------------------------------------------------------------------------

bool Text::Init()
{
	if (TTF_WasInit() == 0 && TTF_Init() == -1)
	{
		std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------

void Text::Quit()
{
	TTF_Quit();
}

//--------------------------------------------------------------------------------------------------
