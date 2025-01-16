#include "Circle.h"
#include "Window.h"

//--------------------------------------------------------------------------------------------------

Circle::Circle() :
	radius{ 50 }
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

	int x0{ int(position.x) };
	int y0{ int(position.y) };

	int offset{ ~int(radius * 2) & 1 };

	// Calcula os pontos para um quadrante e espelha nos demais
	for (size_t i{}; i < precision; ++i)
	{
		int x1{ int(radius * cosf(i * step)) };
		int y1{ int(radius * sinf(i * step)) };

		points[i] = { x0 + x1, y0 - y1 - offset };
		points[halfSize - 1 - i] = { x0 - x1 - offset, y0 - y1 - offset };
		points[halfSize + i] = { x0 - x1 - offset, y0 + y1 };
		points[size - 1 - i] = { x0 + x1, y0 + y1 };
	}

	window->SetRenderDrawColor(color);
	window->DrawLines(points, size);
}

//--------------------------------------------------------------------------------------------------

bool Circle::CheckCollision(const Circle* other) const
{
	// Calcula a distância entre os centros dos dois círculos
	float dx{ this->position.x - other->position.x };
	float dy{ this->position.y - other->position.y };
	float distanceSquared{ dx * dx + dy * dy };

	// Verifica se a soma dos raios é maior ou igual à distância entre os centros
	float radiusSum{ this->Radius() + other->Radius() };

	return distanceSquared <= (radiusSum * radiusSum);
}

//--------------------------------------------------------------------------------------------------
