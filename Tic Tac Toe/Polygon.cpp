#include "Polygon.h"
#include "Window.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

Polygon::Polygon(std::initializer_list<Vector2i> list) :
	origin{},
	vertices{},
	size{ list.size() }
{
	origin = new Vector2i[size];
	vertices = new Vector2i[Size()];

	std::copy(list.begin(), list.end(), origin);

	Refresh();
}

//--------------------------------------------------------------------------------------------------

Polygon::~Polygon()
{
	delete[] origin;
	delete[] vertices;
}

//--------------------------------------------------------------------------------------------------

void Polygon::Refresh()
{
	// Cálculo de seno e cosseno
	float cosAngle{ cosf(this->angle.radians) };
	float sinAngle{ sinf(this->angle.radians) };

	// Aplica a rotação e atualiza vertices
	for (int i{}; i < size; ++i)
	{
		float rotatedX{ origin[i].x * cosAngle - origin[i].y * sinAngle };
		float rotatedY{ origin[i].x * sinAngle + origin[i].y * cosAngle };

		vertices[i].x = int(position.x + rotatedX);
		vertices[i].y = int(position.y + rotatedY);
	}
	vertices[size] = vertices[0];
}

//--------------------------------------------------------------------------------------------------

void Polygon::Draw(Window* window) const
{
	window->SetRenderDrawColor(color);
	window->DrawLines(vertices, unsigned(Size()));
}

//--------------------------------------------------------------------------------------------------

bool Polygon::CheckCollision(const Polygon* other) const
{
	return false;
}

//--------------------------------------------------------------------------------------------------
