#include "Point.h"
#include "Window.h"
#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

Point::Point(const Vector2f& position)
{
	Position(position);
}

//--------------------------------------------------------------------------------------------------

Point::Point(const Vector2i& position)
{
	Position(position);
}

//--------------------------------------------------------------------------------------------------

void Point::Draw(Window* window) const
{
	constexpr int radius{ 3 }; // Distância dos pontos ao redor do ponto central
	constexpr int offset{ radius - 1 };

	window->SetRenderDrawColor(color);

	// Desenha um retângulo sobre o ponto central
	Rect rect{
		int(position.x) - offset,
		int(position.y) - offset,
		radius + offset,
		radius + offset
	};
	window->DrawRect(&rect, true);

	// Desenha os 4 pontos suplementares
	for (int i{}; i < 4; i++)
	{
		int dx{ radius * (i & 1) * ((i & 2) - 1) }; // Deslocamento no eixo x
		int dy{ radius * (~i & 1) * ((i & 2) - 1) }; // Deslocamento no eixo y
		window->DrawPoint(int(position.x + dx), int(position.y + dy));
	}
}

//--------------------------------------------------------------------------------------------------
