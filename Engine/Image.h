#ifndef QUANTVERSO_IMAGE_H
#define QUANTVERSO_IMAGE_H

//--------------------------------------------------------------------------------------------------

#include <SDL_image.h>
#include "Transformable.h"

class Color;

//--------------------------------------------------------------------------------------------------

class Image
{
public:
	Image();
	virtual ~Image();

	void Load(const char* file);

	const Rect& GetRect() const;
	Color GetPixelColor(int x, int y) const;
	bool ComparePixelColor(int x, int y, Color color, unsigned tolerance = 100) const;

protected:
	SDL_Surface* m_Surface;
	Rect		 m_Rect;

private:
	friend class Window;
	
	static bool Init();
	static void Quit();
	static bool HasActiveInstances();	
};

//--------------------------------------------------------------------------------------------------

inline const Rect& Image::GetRect() const
{
	return m_Rect;
}

//--------------------------------------------------------------------------------------------------

#endif
