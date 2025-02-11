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

	window->SetRenderDrawColor(m_Color);

	// Desenha um retângulo sobre o ponto central
	Rect rect{
		int(m_Position.x) - offset,
		int(m_Position.y) - offset,
		radius + offset,
		radius + offset
	};
	SDL_RenderFillRect(window->GetRenderer(), &rect);

	// Desenha os 4 pontos suplementares
	for (int i{}; i < 4; i++)
	{
		int dx{ radius * (i & 1) * ((i & 2) - 1) }; // Deslocamento no eixo x
		int dy{ radius * (~i & 1) * ((i & 2) - 1) }; // Deslocamento no eixo y
		window->DrawPoint(int(m_Position.x + dx), int(m_Position.y + dy));
	}
}

//--------------------------------------------------------------------------------------------------
