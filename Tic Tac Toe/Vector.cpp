#include "Vector.h"

//--------------------------------------------------------------------------------------------------

Vector::Vector() :
	magnitude{}
{
}

//--------------------------------------------------------------------------------------------------

Vector::Vector(float angle, float magnitude) :
	magnitude{ magnitude }
{
	Rotation(angle);
}

//--------------------------------------------------------------------------------------------------

void Vector::Add(const Vector& vector)
{
	// Soma as componentes dos vetores
	float rx{ Component().x + vector.Component().x };
	float ry{ Component().y + vector.Component().y };

	// Calcula a magnitude
	magnitude = std::hypotf(rx, ry);

	// Calcula o ângulo em radianos e converte para graus
	angle.degrees = float((angle.radians = std::atan2f(ry, rx)) * 180 / M_PI);
}

//--------------------------------------------------------------------------------------------------
