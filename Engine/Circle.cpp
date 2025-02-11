#include "Circle.h"
#include "Window.h"

//--------------------------------------------------------------------------------------------------

Circle::Circle() :
	m_Radius{ 50 }
{
}

//--------------------------------------------------------------------------------------------------

void Circle::Draw(Window* window) const
{
	constexpr size_t precision{ 25 };	    // Menor precisão por quadrante
	constexpr size_t size{ precision * 4 }; // Tamanho do vetor de pontos
	constexpr size_t halfSize{ size / 2 };  // Metade do tamanho do vetor
	constexpr float  step{ float(M_PI / (2 * precision)) }; // Passo para iterar pelo primeiro quadrante
	static Vector2i  points[size]; // Armazena os pontos dos quadrantes

	int x0{ int(m_Position.x) };
	int y0{ int(m_Position.y) };

	int offset{ ~int(m_Radius * 2) & 1 };

	// Calcula os pontos para um quadrante e espelha nos demais
	for (size_t i{}; i < precision; ++i)
	{
		int x1{ int(m_Radius * cosf(i * step)) };
		int y1{ int(m_Radius * sinf(i * step)) };

		points[i] = { x0 + x1, y0 - y1 - offset };
		points[halfSize - 1 - i] = { x0 - x1 - offset, y0 - y1 - offset };
		points[halfSize + i] = { x0 - x1 - offset, y0 + y1 };
		points[size - 1 - i] = { x0 + x1, y0 + y1 };
	}

	window->SetRenderDrawColor(m_Color);
	window->DrawLines(points, size);
}

//--------------------------------------------------------------------------------------------------

bool Circle::CheckCollision(const Circle* other) const
{
	// Calcula a distância entre os centros dos dois círculos
	float dx{ this->m_Position.x - other->m_Position.x };
	float dy{ this->m_Position.y - other->m_Position.y };
	float distanceSquared{ dx * dx + dy * dy };

	// Verifica se a soma dos raios é maior ou igual à distância entre os centros
	float radiusSum{ this->GetRadius() + other->GetRadius() };

	return distanceSquared <= (radiusSum * radiusSum);
}

//--------------------------------------------------------------------------------------------------
