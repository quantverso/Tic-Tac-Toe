#ifndef QUANTVERSO_SHAPE_H
#define QUANTVERSO_SHAPE_H

//--------------------------------------------------------------------------------------------------

#include "Transformable.h"
#include "Color.h"

class Rectangle;
class Circle;
class Point;
class Polygon;
class Window;

//--------------------------------------------------------------------------------------------------

class Shape : public Transformable
{
public:
	Shape();
	virtual ~Shape() = default;

	void SetColor(Color color);

	virtual bool CheckCollision(const Shape* other) const = 0;
	virtual bool CheckCollision(const Rectangle* other) const = 0;
	virtual bool CheckCollision(const Circle* other) const = 0;
	virtual bool CheckCollision(const Point* other) const = 0;
	virtual bool CheckCollision(const Polygon* other) const = 0;

	bool CheckCollision(const Rectangle* rect, const Circle* circle) const;
	bool CheckCollision(const Rectangle* rect, const Point* point) const;
	bool CheckCollision(const Rectangle* rect, const Polygon* polygon) const;
	bool CheckCollision(const Circle* circle, const Point* point) const;
	bool CheckCollision(const Circle* circle, const Polygon* polygon) const;
	bool CheckCollision(const Point* point, const Polygon* polygon) const;

protected:
	Color m_Color;

private:
	friend class Window;

	virtual void Draw(Window* window) const = 0;
};

//--------------------------------------------------------------------------------------------------

inline void Shape::SetColor(Color color)
{
	m_Color = color;
}

//--------------------------------------------------------------------------------------------------

#endif
