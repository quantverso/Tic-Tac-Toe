#include "Image.h"
#include "Color.h"
#include "Engine.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------

Image::Image() :
	size{},
	surface{}
{
	if (instances++ == 0 && !(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
		std::cerr << "Erro ao inicializar SDL_Image: " << IMG_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

Image::~Image()
{
	if (surface)
		SDL_FreeSurface(surface);

	if (--instances == 0)
	{
		IMG_Quit();
		Engine::window.Close();
	}
}

//--------------------------------------------------------------------------------------------------

void Image::Load(const char* file)
{
	if (surface)
	{
		SDL_FreeSurface(surface);
		surface = nullptr;
	}

	if (surface = IMG_Load(file))
	{
        if (surface->format->BitsPerPixel != 32)
        {
            if (auto converted{ SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0) })
            {
                SDL_FreeSurface(surface);
                surface = converted;
            }
            else
                std::cerr << "Falha ao converter a superfície para 32 bits: " << SDL_GetError() << std::endl;
        }

		size.width = float(surface->w);
		size.height = float(surface->h);
	}		
	else
		std::cerr << "Falha ao carregar imagem: " << IMG_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

Color Image::GetPixelColor(int x, int y) const
{
    Color color{};

    if (!surface)
    {
        std::cerr << "Falha ao acessar superfície de imagem: " << IMG_GetError() << std::endl;
        return color;
    }

    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
    {
        std::cerr << "Coordenadas fora dos limites da imagem." << std::endl;
        return color;
    }

    SDL_LockSurface(surface);

    Uint32* pixels{ (Uint32*)surface->pixels };
    Uint32 pixelColor{ pixels[y * surface->w + x] };

    SDL_GetRGBA(pixelColor, surface->format, &color.r, &color.g, &color.b, &color.a);

    SDL_UnlockSurface(surface);

    return color;
}

//--------------------------------------------------------------------------------------------------

bool Image::ComparePixelColor(int x, int y, Color color, unsigned tolerance) const
{
	// Cor do pixel
	auto pixelColor{ GetPixelColor(x, y) };

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
