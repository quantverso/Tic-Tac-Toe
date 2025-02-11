#ifndef QUANTVERSO_POINT_H
#define QUANTVERSO_POINT_H

//--------------------------------------------------------------------------------------------------

#include "Shape.h"

//--------------------------------------------------------------------------------------------------

class Point : public Shape
{
public:
	Point() = default;
	Point(const Vector2f& position);
	Point(const Vector2i& position);

	bool CheckCollision(const Shape* other) const;
	bool CheckCollision(const Rectangle* other) const;
	bool CheckCollision(const Circle* other) const;
	bool CheckCollision(const Polygon* other) const;
	bool CheckCollision(const Point* other) const;

private:
	void Draw(Window* window) const;	
};

//--------------------------------------------------------------------------------------------------

inline bool Point::CheckCollision(const Shape* other) const
{
	return other->CheckCollision(this);
}

//--------------------------------------------------------------------------------------------------

inline bool Point::CheckCollision(const Rectangle* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline bool Point::CheckCollision(const Circle* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline bool Point::CheckCollision(const Polygon* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

inline bool Point::CheckCollision(const Point* other) const
{
	return this->m_Position.x == other->m_Position.x && this->m_Position.y == other->m_Position.y;
}

//--------------------------------------------------------------------------------------------------

#endif
