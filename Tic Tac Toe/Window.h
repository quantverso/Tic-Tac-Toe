#ifndef QUANTVERSO_WINDOW_H
#define QUANTVERSO_WINDOW_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include "Transformable.h"
#include "Color.h"
#include "Texture.h"
#include "Text.h"
#include "Shape.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <bitset>
#include <iostream>

//--------------------------------------------------------------------------------------------------

class Window
{
public:
	enum Event
	{
		Quit            = SDL_QUIT,
		MouseButtonDown = SDL_MOUSEBUTTONDOWN,
		MouseButtonUp   = SDL_MOUSEBUTTONUP
	};

	Window();
	~Window();
	
	void Create();
	void Create(const char* title, unsigned width, unsigned height);
	void Size(unsigned width, unsigned height);
	void Title(const char* title);
	void Close();
	void WatchEvents();		
	void Clear(Color color = Color::Black);
	void Display();
	void SetRenderDrawColor(Color color);
	void SetViewport(Rect* area = nullptr);
	void DrawPoint(int x, int y);
	void DrawPoints(const Vector2i* points, unsigned count);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLines(const Vector2i* points, unsigned count);
	void DrawRect(const Rect* rect, bool filled);
	void Draw(const Shape* shape);
	void Draw(const Text* text);
	void Draw(
		const Texture* texture,
		const Rect* srcRect = nullptr,
		const Rect* dstRect = nullptr,
		float angle = 0,
		const Vector2i* offset = nullptr);
	
	bool IsOpen() const;
	bool CheckEvent(Event event);
	const char* Title();

	static const ::Size& Size();
	static Vector2f Center();

private:
	friend class Texture;
	friend class Text;

	static ::Size size;

	SDL_Window*	  window;
	SDL_Renderer* renderer;
	SDL_Event	  event;
	std::bitset<MouseButtonUp + 1> events;
	const char*	  title;
	
};

//--------------------------------------------------------------------------------------------------

inline bool Window::IsOpen() const
{
	return window;
}

//--------------------------------------------------------------------------------------------------

inline void Window::WatchEvents()
{
	events.reset();
	while (SDL_PollEvent(&event))
		events[event.type] = true;
}

//--------------------------------------------------------------------------------------------------

inline bool Window::CheckEvent(Event event)
{
	return events[event];
}

//--------------------------------------------------------------------------------------------------

inline void Window::Clear(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Display()
{
	SDL_RenderPresent(renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::SetRenderDrawColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

//--------------------------------------------------------------------------------------------------

inline void Window::SetViewport(Rect* area)
{
	SDL_RenderSetViewport(renderer, area);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawPoints(const Vector2i* points, unsigned count)
{
	SDL_RenderDrawPoints(renderer, points, count);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawLines(const Vector2i* points, unsigned count)
{
	SDL_RenderDrawLines(renderer, points, count);
}

//--------------------------------------------------------------------------------------------------

inline void Window::DrawRect(const Rect* rect, bool filled)
{
	filled ? SDL_RenderFillRect(renderer, rect) : SDL_RenderDrawRect(renderer, rect);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(const Shape* shape)
{
	shape->Draw(this);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(const Text* text)
{
	SDL_RenderCopy(renderer, text->texture, nullptr, &text->rect);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(
	const Texture* texture,
	const Rect* srcRect,
	const Rect* dstRect,
	float angle,
	const Vector2i* offset)
{
	if (angle)
		SDL_RenderCopyEx(renderer, texture->texture, srcRect, dstRect, angle, offset, SDL_FLIP_NONE);
	else
		SDL_RenderCopy(renderer, texture->texture, srcRect, dstRect);
}

//--------------------------------------------------------------------------------------------------

inline const char* Window::Title()
{
	return title;
}

//--------------------------------------------------------------------------------------------------

inline const ::Size& Window::Size()
{
	return size;
}

//--------------------------------------------------------------------------------------------------

inline Vector2f Window::Center()
{
	return { size.width / 2.f, size.height / 2.f };
}

//--------------------------------------------------------------------------------------------------

#endif
