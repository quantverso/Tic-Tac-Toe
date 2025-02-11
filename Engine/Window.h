#ifndef QUANTVERSO_WINDOW_H
#define QUANTVERSO_WINDOW_H

//--------------------------------------------------------------------------------------------------

#include "Keyboard.h"
#include "Mouse.h"
#include "Transformable.h"
#include "Color.h"
#include "Texture.h"
#include "Text.h"
#include "Shape.h"
#include <SDL.h>
#include <bitset>
#include <iostream>

//--------------------------------------------------------------------------------------------------

class Window
{
public:
	enum Event
	{
		Quit            = SDL_QUIT,
		KeyDown			= SDL_KEYDOWN,
		KeyUp			= SDL_KEYUP,
		MouseMotion		= SDL_MOUSEMOTION,
		MouseButtonDown = SDL_MOUSEBUTTONDOWN,
		MouseButtonUp   = SDL_MOUSEBUTTONUP,
		MouseWheel		= SDL_MOUSEWHEEL
	};
	using EventBitset = std::bitset<MouseWheel + 1>;

	Window();
	~Window();
	
	void Create();
	void Create(const char* title, unsigned width, unsigned height);
	void SetSize(unsigned width, unsigned height);
	void SetTitle(const char* title);
	void Close();
	void PollEvents();
	void Clear(Color color = Color::Black);
	void Display();
	void SetRenderDrawColor(Color color);
	void DrawPoint(int x, int y);
	void DrawPoints(const Vector2i* points, unsigned count);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLines(const Vector2i* points, unsigned count);
	void Draw(const Shape* shape);
	void Draw(const Text* text);
	void Draw(const Texture* texture, const Rect* srcRect = nullptr, const Rect* dstRect = nullptr,	float angle = 0.f, const Vector2i* offset = nullptr);
	
	bool IsOpen() const;
	bool IsEventTriggered(Event e) const;
	SDL_Renderer* GetRenderer() const;
	const char* GetTitle() const;

	static const Size& GetSize();

private:
	static Size   s_Size;

	SDL_Window*	  m_Window;
	SDL_Renderer* m_Renderer;
	EventBitset	  m_Events;
	const char*	  m_Title;
	
};

//--------------------------------------------------------------------------------------------------

inline void Window::PollEvents()
{
	m_Events.reset();
	static SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type < m_Events.size())
			m_Events[event.type] = true;
	}
}

//--------------------------------------------------------------------------------------------------

inline void Window::Clear(Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Display()
{
	SDL_RenderPresent(m_Renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::SetRenderDrawColor(Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(m_Renderer, x, y);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawPoints(const Vector2i* points, unsigned count)
{
	SDL_RenderDrawPoints(m_Renderer, points, count);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawLines(const Vector2i* points, unsigned count)
{
	SDL_RenderDrawLines(m_Renderer, points, count);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(const Shape* shape)
{
	shape->Draw(this);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(const Text* text)
{
	SDL_RenderCopy(m_Renderer, text->m_Texture, nullptr, &text->m_Rect);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(const Texture* texture, const Rect* srcRect, const Rect* dstRect, float angle, const Vector2i* offset)
{
	if (angle)
		SDL_RenderCopyEx(m_Renderer, texture->m_Texture, srcRect, dstRect, angle, offset, SDL_FLIP_NONE);
	else
		SDL_RenderCopy(m_Renderer, texture->m_Texture, srcRect, dstRect);
}

//--------------------------------------------------------------------------------------------------

inline bool Window::IsOpen() const
{
	return m_Window;
}

//--------------------------------------------------------------------------------------------------

inline bool Window::IsEventTriggered(Event e) const
{
	return m_Events[e];
}

//--------------------------------------------------------------------------------------------------

inline SDL_Renderer* Window::GetRenderer() const
{
	return m_Renderer;
}

//--------------------------------------------------------------------------------------------------

inline const char* Window::GetTitle() const
{
	return m_Title;
}

//--------------------------------------------------------------------------------------------------

inline const Size& Window::GetSize()
{
	return s_Size;
}

//--------------------------------------------------------------------------------------------------

#endif
