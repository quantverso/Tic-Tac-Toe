#ifndef QUANTVERSO_COLOR_H
#define QUANTVERSO_COLOR_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>

//--------------------------------------------------------------------------------------------------

class Color : public SDL_Color
{
public:
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Magenta;
	static const Color Cyan;
	
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	Color(const Color& other);

	Color& operator=(const Color& other);	
};

//--------------------------------------------------------------------------------------------------

inline Color& Color::operator=(const Color& other)
{
	if (this != &other)
		SDL_Color::operator=(other);

	return *this;
}

//--------------------------------------------------------------------------------------------------

#endif
