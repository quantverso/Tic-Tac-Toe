#ifndef QUANTVERSO_TEXT_H
#define QUANTVERSO_TEXT_H

//--------------------------------------------------------------------------------------------------

#include "SDL_ttf.h"
#include "Texture.h"
#include "Color.h"
#include <string>

class Window;

//--------------------------------------------------------------------------------------------------

class Text : Texture
{
public:
	using Image::GetRect;

	Text();
	~Text();

	void Load(const char* file, unsigned size);
	void SetString(const std::string& string);
	void Position(int x, int y);
	void SetSize(int w, int h);
	void SetSize(float w, float h);
	void SetColor(Color color);

private:
	friend class Window;

	std::string	m_Text;  ///< Texto a ser renderizado
	unsigned	m_Size;  ///< Tamanho da fonte
	Color		m_Color; ///< Cor do texto
	TTF_Font*	m_Font;  ///< Fonte carregada do arquivo .ttf

	static bool Init();
	static void Quit();
};

//--------------------------------------------------------------------------------------------------

#endif
