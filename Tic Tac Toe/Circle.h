#ifndef QUANTVERSO_CIRCLE_H
#define QUANTVERSO_CIRCLE_H

//--------------------------------------------------------------------------------------------------

#include "Shape.h"

//--------------------------------------------------------------------------------------------------

class Circle : public Shape
{
public:
	Circle();

	void Radius(float radius);
	const float& Radius() const;

	bool CheckCollision(const Shape* other) const;
	bool CheckCollision(const Rectangle* other) const;
	bool CheckCollision(const Circle* other) const;
	bool CheckCollision(const Point* other) const;
	bool CheckCollision(const Polygon* other) const;

private:
	float radius;

	void Draw(Window* window) const;	
};

//--------------------------------------------------------------------------------------------------

inline void Circle::Radius(float radius)
{
	this->radius = radius;
}

//--------------------------------------------------------------------------------------------------

inline const float& Circle::Radius() const
{
	return radius;
}

//--------------------------------------------------------------------------------------------------

inline bool Circle::CheckCollision(const Shape* other) const
{
	return other->CheckCollision(this);
}

//--------------------------------------------------------------------------------------------------

inline bool Circle::CheckCollision(const Rectangle* other) const
{
	return Shape::CheckCollision(other, this);
}

//--------------------------------------------------------------------------------------------------

inline bool Circle::CheckCollision(const Point* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

inline bool Circle::CheckCollision(const Polygon* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

#endif
