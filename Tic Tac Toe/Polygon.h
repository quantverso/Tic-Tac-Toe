#ifndef QUANTVERSO_POLYGON_H
#define QUANTVERSO_POLYGON_H

//--------------------------------------------------------------------------------------------------

#include "Shape.h"
#include "Rotatable.h"
#include <initializer_list>

//--------------------------------------------------------------------------------------------------

class Polygon : public Shape, public Rotatable
{
public:
	Polygon(std::initializer_list<Vector2i> list);
	~Polygon();

	size_t Size() const;

	bool CheckCollision(const Shape* other) const;
	bool CheckCollision(const Rectangle* other) const;
	bool CheckCollision(const Circle* other) const;
	bool CheckCollision(const Point* other) const;
	bool CheckCollision(const Polygon* other) const;

	const Vector2i& operator[](std::size_t index) const;

private:
	Vector2i* origin;
	Vector2i* vertices;
	size_t	  size;

	void Refresh();
	void Draw(Window* window) const;
};

//--------------------------------------------------------------------------------------------------

inline size_t Polygon::Size() const
{
	return size + 1;
}

//--------------------------------------------------------------------------------------------------

inline bool Polygon::CheckCollision(const Shape* other) const
{
	return other->CheckCollision(this);
}

//--------------------------------------------------------------------------------------------------

inline bool Polygon::CheckCollision(const Rectangle* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline bool Polygon::CheckCollision(const Circle* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline bool Polygon::CheckCollision(const Point* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline const Vector2i& Polygon::operator[](std::size_t index) const
{
	return vertices[index];
}

//--------------------------------------------------------------------------------------------------

#endif
