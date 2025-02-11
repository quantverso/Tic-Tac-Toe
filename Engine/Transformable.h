#ifndef QUANTVERSO_TRANSFORMABLE_H
#define QUANTVERSO_TRANSFORMABLE_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>

using Rect     = SDL_Rect;
using Vector2i = SDL_Point;

//--------------------------------------------------------------------------------------------------

struct Vector2f
{
	float x, y;
};

//--------------------------------------------------------------------------------------------------

struct Size
{
	float width, height, centerX, centerY;
};

//--------------------------------------------------------------------------------------------------

class Transformable
{
public:
	virtual ~Transformable() = default;

	void Position(float x, float y);
	void Position(int x, int y);
	void Position(const Vector2f& position);	
	void Position(const Vector2i& position);
	void Move(float x, float y);
	void SetScale(float scale);

	const Vector2f& Position() const;

protected:
	Vector2f m_Position{};
	float	 m_Scale{ 1 };

	virtual void Refresh() {};
};

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(int x, int y)
{
	m_Position.x = float(x);
	m_Position.y = float(y);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(const Vector2f& position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(const Vector2i& position)
{
	m_Position.x = float(position.x);
	m_Position.y = float(position.y);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Move(float x, float y)
{
	Position(m_Position.x + x, m_Position.y + y);
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::SetScale(float scale)
{
	m_Scale = scale;
}

//--------------------------------------------------------------------------------------------------

inline const Vector2f& Transformable::Position() const
{
	return m_Position;
}

//--------------------------------------------------------------------------------------------------

#endif
