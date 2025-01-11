#include "Window.h"

//--------------------------------------------------------------------------------------------------

Size Window::size{ 640, 480 };

//--------------------------------------------------------------------------------------------------

Window::Window() :
	window{},
	renderer{},
	event{},
	title{ "Window" }
{	
}

//--------------------------------------------------------------------------------------------------

Window::~Window()
{
	Close();
}

//--------------------------------------------------------------------------------------------------

void Window::Create()
{	
	if (!window)
	{
		// Inicializa a SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
			return;
		}

		// Cria a janela gráfica
		if (!(window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			int(size.width),
			int(size.height),
			SDL_WINDOW_SHOWN)))
		{
			std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return;
		}

		// Cria o renderizador
		if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
		{
			std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
			Close();
		}
		else
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}
}

//--------------------------------------------------------------------------------------------------

void Window::Create(const char* title, unsigned width, unsigned height)
{
	if (!window)
	{
		this->title = title;
		Size(width, height);
		Create();
	}
}

//--------------------------------------------------------------------------------------------------

void Window::Size(unsigned width, unsigned height)
{
	size.width = float(width);
	size.height = float(height);

	if (window)
		SDL_SetWindowSize(window, width, height);
}

//--------------------------------------------------------------------------------------------------

void Window::Title(const char* title)
{
	this->title = title;

	if (window)
		SDL_SetWindowTitle(window, title);
}

//--------------------------------------------------------------------------------------------------

void Window::Close()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;

		if (Image::instances + Text::instances == 0)
			SDL_Quit();
	}
}

//--------------------------------------------------------------------------------------------------
