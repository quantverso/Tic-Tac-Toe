#include "Image.h"
#include "Color.h"
#include "Engine.h"
#include <cstdlib>
#include <iostream>

//--------------------------------------------------------------------------------------------------

static int instanceCount;

//--------------------------------------------------------------------------------------------------

Image::Image() :
	m_Surface{},
	m_Rect{}
{
	instanceCount++;
}

//--------------------------------------------------------------------------------------------------

Image::~Image()
{
	if (m_Surface)
		SDL_FreeSurface(m_Surface);

	if (--instanceCount == 0 && !Engine::window.IsOpen())
		Engine::window.Close();
}

//--------------------------------------------------------------------------------------------------

void Image::Load(const char* file)
{
	if (m_Surface)
	{
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
	}

	m_Surface = IMG_Load(file);
	if (!m_Surface)
	{
		std::cerr << "Falha ao carregar imagem: " << IMG_GetError() << std::endl;
		return;
	}

	if (m_Surface->format->BitsPerPixel != 32)
	{
		SDL_Surface* converted{ SDL_ConvertSurfaceFormat(m_Surface, SDL_PIXELFORMAT_RGBA32, 0) };
		if (!converted)
		{
			std::cerr << "Falha ao converter a superfície para 32 bits: " << SDL_GetError() << std::endl;
			return;
		}

		SDL_FreeSurface(m_Surface);
		m_Surface = converted;
	}

	m_Rect.w = m_Surface->w;
	m_Rect.h = m_Surface->h;
}

//--------------------------------------------------------------------------------------------------

Color Image::GetPixelColor(int x, int y) const
{
	Color color{};

	if (!m_Surface)
	{
		std::cerr << "Falha ao acessar superficie de imagem: " << IMG_GetError() << std::endl;
		return color;
	}

	if (x < 0 || x >= m_Surface->w || y < 0 || y >= m_Surface->h)
	{
		std::cerr << "Coordenadas fora dos limites da imagem." << std::endl;
		return color;
	}

	SDL_LockSurface(m_Surface);

	Uint32* pixels{ (Uint32*)m_Surface->pixels };
	Uint32 pixelColor{ pixels[y * m_Surface->w + x] };

	SDL_GetRGBA(pixelColor, m_Surface->format, &color.r, &color.g, &color.b, &color.a);

	SDL_UnlockSurface(m_Surface);

	return color;
}

//--------------------------------------------------------------------------------------------------

bool Image::ComparePixelColor(int x, int y, Color color, unsigned tolerance) const
{
	// Cor do pixel
	Color pixelColor{ GetPixelColor(x, y) };

	// Diferença total entre componentes RGBA
	int difference{
		abs(pixelColor.r - color.r) +
		abs(pixelColor.g - color.g) +
		abs(pixelColor.b - color.b) +
		abs(pixelColor.a - color.a)
	};

	// Compara a diferença total com o limite permitido pela tolerância.
	return difference <= ((4 * 255) * int(tolerance) / 100);
}

//--------------------------------------------------------------------------------------------------

bool Image::Init()
{
	if (IMG_Init(0) == 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		std::cerr << "Erro ao inicializar SDL_Image: " << IMG_GetError() << std::endl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------

void Image::Quit()
{
	IMG_Quit();
}

//--------------------------------------------------------------------------------------------------

bool Image::HasActiveInstances()
{
	return instanceCount > 0;
}

//--------------------------------------------------------------------------------------------------
