#ifndef QUANTVERSO_TEXTURE_H
#define QUANTVERSO_TEXTURE_H

//--------------------------------------------------------------------------------------------------

#include "Image.h"

class Color;

//--------------------------------------------------------------------------------------------------

class Texture : Image
{
public:
	using Image::Size;

	Texture();
	Texture(const char* file);
	~Texture();
	void Load(const char* file);
	void Color(::Color color);

private:
	friend class Window;

	SDL_Texture* texture;
};

//--------------------------------------------------------------------------------------------------

#endif
