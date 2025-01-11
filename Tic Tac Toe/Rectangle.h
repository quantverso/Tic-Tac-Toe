#ifndef QUANTVERSO_RECTANGLE_H
#define QUANTVERSO_RECTANGLE_H

//--------------------------------------------------------------------------------------------------

#include "Shape.h"
#include "Window.h"

//--------------------------------------------------------------------------------------------------

class Rectangle : protected Rect, public Shape
{
public:
	enum Fill
	{
		None,
		Solid
	};

	struct Bounds
	{
		Bounds(const Rectangle* rect) :
			rect{ rect }
		{
		}

		const int& Left() const { return rect->x; }
		const int& Top() const { return rect->y; }
		int Right() const { return rect->x + rect->w; }
		int Bottom() const { return rect->y + rect->h; }

	private:
		const Rectangle* rect;
	};
	
	Bounds bounds;

	Rectangle(Fill fill = None);

	void Size(float width, float height);
	void Scale(float scale);
	void Origin(float x, float y);

	const ::Size& Size() const;
	const ::Size& Center() const;

	bool CheckCollision(const Shape* other) const;
	bool CheckCollision(const Circle* other) const;
	bool CheckCollision(const Point* other) const;
	bool CheckCollision(const Polygon* other) const;
	bool CheckCollision(const Rectangle* other) const;

protected:
	::Size size;
	Offset offset;

	void Refresh();

private:
	friend class Window;

	const bool fill;

	void Draw(Window* window) const;
	
};

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Size(float width, float height)
{
	size.width = width;
	size.height = height;
	offset.Update(width, height);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Scale(float scale)
{
	Transformable::Scale(scale);
	Size(size.width * scale, size.height * scale);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Origin(float x, float y)
{
	offset.Position(x, y, size.width, size.height);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline const ::Size& Rectangle::Size() const
{
	return size;
}

//--------------------------------------------------------------------------------------------------

inline const::Size& Rectangle::Center() const
{
	return { x + size.width / 2, y + size.height / 2 };
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Refresh()
{
	x = int(position.x) - offset.X();
	y = int(position.y) - offset.Y();
	w = int(size.width);
	h = int(size.height);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Draw(Window* window) const
{
	window->SetRenderDrawColor(color);
	window->DrawRect(this, fill);
}

//--------------------------------------------------------------------------------------------------

inline bool Rectangle::CheckCollision(const Shape* other) const
{
	return other->CheckCollision(this);
}

//--------------------------------------------------------------------------------------------------

inline bool Rectangle::CheckCollision(const Circle* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

inline bool Rectangle::CheckCollision(const Point* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

inline bool Rectangle::CheckCollision(const Polygon* other) const
{
	return Shape::CheckCollision(this, other);
}

//--------------------------------------------------------------------------------------------------

#endif
