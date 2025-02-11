#include "Window.h"

//--------------------------------------------------------------------------------------------------

Size Window::s_Size{ 640, 480, 320, 240 };

//--------------------------------------------------------------------------------------------------

Window::Window() :
	m_Window{},
	m_Renderer{},
	m_Title{ "Window" }
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
	if (!m_Window)
	{
		// Inicializa a SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
			return;
		}

		// Cria a janela
		m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, int(s_Size.width), int(s_Size.height), SDL_WINDOW_SHOWN);
		if (!m_Window)
		{
			std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return;
		}

		// Cria o renderizador
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (!m_Renderer)
		{
			std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
			Close();
			return;
		}

		// Habilita mistura para desenhar com transparência.
		SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

		// Inicializa SDL_image e SDL_ttf
		Image::Init();
		Text::Init();
	}
}

//--------------------------------------------------------------------------------------------------

void Window::Create(const char* title, unsigned width, unsigned height)
{
	if (!m_Window)
	{
		m_Title = title;
		SetSize(width, height);
		Create();
	}
}

//--------------------------------------------------------------------------------------------------

void Window::SetSize(unsigned width, unsigned height)
{
	s_Size.width = float(width);
	s_Size.height = float(height);
	s_Size.centerX = width / 2.f;
	s_Size.centerY = height / 2.f;

	if (m_Window)
		SDL_SetWindowSize(m_Window, width, height);
}

//--------------------------------------------------------------------------------------------------

void Window::SetTitle(const char* title)
{
	m_Title = title;

	if (m_Window)
		SDL_SetWindowTitle(m_Window, title);
}

//--------------------------------------------------------------------------------------------------

void Window::Close()
{
	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}

	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	if (!Image::HasActiveInstances())
	{
		Image::Quit();
		Text::Quit();
		SDL_Quit();
	}
}

//--------------------------------------------------------------------------------------------------
