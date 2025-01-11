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
	static const int   precision{ 25 };	      // Menor precis�o por quadrante
	static const int   size{ precision * 4 }; // Tamanho do vetor de pontos
	static const int   halfSize{ size / 2 };  // Metade do tamanho do vetor	
	static Vector2i    points[size];		  // Armazena os pontos dos quadrantes
	static const float step{ float(M_PI / (2 * precision)) }; // Passo para iterar pelo primeiro quadrante

	int x0{ int(position.x) };
	int y0{ int(position.y) };

	int offset{ ~int(radius * 2) & 1 };

	// Calcula os pontos para um quadrante e espelha nos demais
	for (int i{}; i < precision; ++i)
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
	// Calcula a dist�ncia entre os centros dos dois c�rculos
	float dx{ this->position.x - other->position.x };
	float dy{ this->position.y - other->position.y };
	float distanceSquared{ dx * dx + dy * dy };

	// Verifica se a soma dos raios � maior ou igual � dist�ncia entre os centros
	float radiusSum{ this->Radius() + other->Radius() };

	return distanceSquared <= (radiusSum * radiusSum);
}

//--------------------------------------------------------------------------------------------------
