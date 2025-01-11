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
	float width, height;
};

//--------------------------------------------------------------------------------------------------

class Transformable
{
public:
	class Offset : SDL_Point
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
		friend class Entity;

		float perX{};
		float perY{};
	};

	virtual ~Transformable() = 0;

	void Position(float x, float y);
	void Position(int x, int y);
	void Position(const Vector2f& position);	
	void Position(const Vector2i& position);
	void Move(float x, float y);
	void Scale(float scale);

	const Vector2f& Position() const;

protected:
	Vector2f position{};
	float	 scale{ 1 };

	virtual void Refresh() {};
};

//--------------------------------------------------------------------------------------------------

inline Transformable::~Transformable()
{
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(float x, float y)
{
	position.x = x;
	position.y = y;
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(int x, int y)
{
	position.x = float(x);
	position.y = float(y);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(const Vector2f& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(const Vector2i& position)
{
	this->position.x = float(position.x);
	this->position.y = float(position.y);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Move(float x, float y)
{
	Position(position.x + x, position.y + y);
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Scale(float scale)
{
	this->scale = scale;
}

//--------------------------------------------------------------------------------------------------

inline const Vector2f& Transformable::Position() const
{
	return position;
}

//--------------------------------------------------------------------------------------------------

#endif
