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

	void SetMagnitude(float magnitude);
	void SetScale(float scale);
	void Add(const Vector& vector);

	const float& GetMagnitude() const;
	Vector2f GetComponent() const;

private:
	float m_Magnitude;
};

//--------------------------------------------------------------------------------------------------

inline void Vector::SetMagnitude(float magnitude)
{
	m_Magnitude = magnitude;
}

//--------------------------------------------------------------------------------------------------

inline void Vector::SetScale(float scale)
{
	m_Magnitude *= scale;
}

//--------------------------------------------------------------------------------------------------

inline const float& Vector::GetMagnitude() const
{
	return m_Magnitude;
}

//--------------------------------------------------------------------------------------------------

inline Vector2f Vector::GetComponent() const
{
	return { m_Magnitude * cosf(m_Angle.radians), m_Magnitude * sinf(m_Angle.radians) };
}

//--------------------------------------------------------------------------------------------------

#endif
