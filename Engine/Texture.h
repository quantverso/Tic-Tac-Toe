#ifndef QUANTVERSO_TEXTURE_H
#define QUANTVERSO_TEXTURE_H

//--------------------------------------------------------------------------------------------------

#include "Image.h"

class Color;

//--------------------------------------------------------------------------------------------------

class Texture : protected Image
{
public:
	using Image::GetRect;

	Texture();
	Texture(const char* file);
	virtual ~Texture();

	void Load(const char* file);
	void SetColor(Color color);

protected:
	friend class Window;

	SDL_Texture* m_Texture;
};

//--------------------------------------------------------------------------------------------------

#endif
