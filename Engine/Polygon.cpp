#include "Polygon.h"
#include "Window.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

Polygon::Polygon(std::initializer_list<Vector2i> list) :
	m_Origin{},
	m_Vertices{},
	m_Size{ list.size() }
{
	m_Origin = new Vector2i[m_Size];
	m_Vertices = new Vector2i[GetSize()];

	std::copy(list.begin(), list.end(), m_Origin);

	Refresh();
}

//--------------------------------------------------------------------------------------------------

Polygon::~Polygon()
{
	delete[] m_Origin;
	delete[] m_Vertices;
}

//--------------------------------------------------------------------------------------------------

void Polygon::Refresh()
{
	// Cálculo de seno e cosseno
	float cosAngle{ cosf(m_Angle.radians) };
	float sinAngle{ sinf(m_Angle.radians) };

	// Aplica a rotação e atualiza vertices
	for (int i{}; i < m_Size; ++i)
	{
		float rotatedX{ m_Origin[i].x * cosAngle - m_Origin[i].y * sinAngle };
		float rotatedY{ m_Origin[i].x * sinAngle + m_Origin[i].y * cosAngle };

		m_Vertices[i].x = int(m_Position.x + rotatedX);
		m_Vertices[i].y = int(m_Position.y + rotatedY);
	}
	m_Vertices[m_Size] = m_Vertices[0];
}

//--------------------------------------------------------------------------------------------------

void Polygon::Draw(Window* window) const
{
	window->SetRenderDrawColor(m_Color);
	window->DrawLines(m_Vertices, unsigned(GetSize()));
}

//--------------------------------------------------------------------------------------------------

bool Polygon::CheckCollision(const Polygon* other) const
{
	return false;
}

//--------------------------------------------------------------------------------------------------
