#include "Vector.h"

//--------------------------------------------------------------------------------------------------

Vector::Vector() :
	m_Magnitude{}
{
}

//--------------------------------------------------------------------------------------------------

Vector::Vector(float angle, float magnitude) :
	m_Magnitude{ magnitude }
{
	SetRotation(angle);
}

//--------------------------------------------------------------------------------------------------

void Vector::Add(const Vector& vector)
{
	// Soma as componentes dos vetores
	float rx{ GetComponent().x + vector.GetComponent().x };
	float ry{ GetComponent().y + vector.GetComponent().y };

	// Calcula a magnitude
	m_Magnitude = std::hypotf(rx, ry);

	// Calcula o ângulo em radianos e converte para graus
	m_Angle.degrees = float((m_Angle.radians = std::atan2f(ry, rx)) * 180 / M_PI);
}

//--------------------------------------------------------------------------------------------------
