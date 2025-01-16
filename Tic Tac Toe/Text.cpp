#include "Text.h"
#include "Engine.h"

//--------------------------------------------------------------------------------------------------

Text::Text() :
	size{},
	font{},
	texture{},
	surface{},
	rect{},
	color{}
{
	if (instances++ == 0 && TTF_Init() == -1)
		std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

Text::~Text()
{
	if (texture)
		SDL_DestroyTexture(texture);

	if (font)
		TTF_CloseFont(font);

	if (--instances == 0)
	{
		TTF_Quit();
		Engine::window.Close();
	}
}

//--------------------------------------------------------------------------------------------------

void Text::Load(const char* file, unsigned size)
{
	this->size = size;

	font = TTF_OpenFont(file, size);
	if (!font)
	{
		std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
		return;
	}

	rect.h = size;
	rect.w = size;
}

//--------------------------------------------------------------------------------------------------

void Text::String(const std::string& string)
{
	text = string;
	rect.w = int(string.size()) * size;

	surface = TTF_RenderText_Solid(font, string.c_str(), color);
	if (!surface)
	{
		std::cerr << "Erro ao criar superficie de texto: " << TTF_GetError() << std::endl;
		return;
	}

	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	texture = texture = SDL_CreateTextureFromSurface(Engine::window.renderer, surface);
	if (!texture)
		std::cerr << "Erro ao criar textura de texto: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(surface);
	surface = nullptr;
}

//--------------------------------------------------------------------------------------------------

void Text::Position(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

//--------------------------------------------------------------------------------------------------

void Text::Size(unsigned w, unsigned h)
{
	size = w;
	rect.w = w;
	rect.h = h;
}

//--------------------------------------------------------------------------------------------------

void Text::Color(::Color color)
{
	this->color = color;
	if (!text.empty())
		String(text);
}

//--------------------------------------------------------------------------------------------------
