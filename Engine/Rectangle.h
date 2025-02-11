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
		const Rectangle* const rect;

	} const bounds;

	void SetSize(float width, float height);
	void SetSize(int width, int height);
	void SetScale(float scale);
	void SetOrigin(float x, float y);

	const Size& GetSize() const;
	const Vector2i& GetOrigin() const;

	bool CheckCollision(const Shape* other) const;
	bool CheckCollision(const Circle* other) const;
	bool CheckCollision(const Point* other) const;
	bool CheckCollision(const Polygon* other) const;
	bool CheckCollision(const Rectangle* other) const;

protected:
	friend class Entity;

	class Offset : public Vector2i
	{
	public:
		void Position(float x, float y, float w, float h)
		{
			this->x = int(x);
			this->y = int(y);

			// Percentual de deslocamento relativo as dimensões.
			perX = x ? w / x : 0;
			perY = y ? h / y : 0;
		}

		void Update(float width, float height)
		{
			x = perX ? int(width / perX) : 0;
			y = perY ? int(height / perY) : 0;
		}

		const int& X() const { return x; }
		const int& Y() const { return y; }

	private:
		float perX{};
		float perY{};

	} m_Offset;

	Size m_Size;

	void Refresh();

private:
	friend class Window;

	Fill m_Fill;

	void Draw(Window* window) const;

public:
	Rectangle(Fill fill = None);
};

//--------------------------------------------------------------------------------------------------

inline void Rectangle::SetSize(float width, float height)
{
	m_Size.width = width;
	m_Size.height = height;
	m_Size.centerX = x + m_Size.width / 2;
	m_Size.centerY = y + m_Size.height / 2;
	m_Offset.Update(width, height);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::SetSize(int width, int height)
{
	SetSize(float(width), float(height));
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::SetScale(float scale)
{
	Transformable::SetScale(scale);
	SetSize(m_Size.width * scale, m_Size.height * scale);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::SetOrigin(float x, float y)
{
	m_Offset.Position(x, y, m_Size.width, m_Size.height);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline const Size& Rectangle::GetSize() const
{
	return m_Size;
}

//--------------------------------------------------------------------------------------------------

inline const Vector2i& Rectangle::GetOrigin() const
{
	return m_Offset;
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Refresh()
{
	x = int(m_Position.x) - m_Offset.X();
	y = int(m_Position.y) - m_Offset.Y();
	w = int(m_Size.width);
	h = int(m_Size.height);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Draw(Window* window) const
{
	window->SetRenderDrawColor(m_Color);
	m_Fill == Solid ? SDL_RenderFillRect(window->GetRenderer(), this) : SDL_RenderDrawRect(window->GetRenderer(), this);
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
