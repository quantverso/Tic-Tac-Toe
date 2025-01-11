#ifndef QUANTVERSO_VECTOR_H
#define QUANTVERSO_VECTOR_H

//--------------------------------------------------------------------------------------------------

#include "Rotatable.h"
#include "Transformable.h"
#include <cmath>

//--------------------------------------------------------------------------------------------------

class Vector : public Rotatable
{
public:
	Vector();
	Vector(float angle, float magnitude);

	void Magnitude(float magnitude);
	void Scale(float scale);
	void Add(const Vector& vector);

	const float& Magnitude() const;
	Vector2f Component() const;

private:
	float magnitude;
};

//--------------------------------------------------------------------------------------------------

inline void Vector::Magnitude(float magnitude)
{
	this->magnitude = magnitude;
}

//--------------------------------------------------------------------------------------------------

inline void Vector::Scale(float scale)
{
	magnitude *= scale;
}

//--------------------------------------------------------------------------------------------------

inline const float& Vector::Magnitude() const
{
	return magnitude;
}

//--------------------------------------------------------------------------------------------------

inline Vector2f Vector::Component() const
{
	return { magnitude * cosf(angle.radians), magnitude * sinf(angle.radians) };
}

//--------------------------------------------------------------------------------------------------

#endif
