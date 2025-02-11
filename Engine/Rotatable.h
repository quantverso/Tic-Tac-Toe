#ifndef QUANTVERSO_ROTATABLE_H
#define QUANTVERSO_ROTATABLE_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>

//--------------------------------------------------------------------------------------------------

struct Angle
{
	float degrees;
	float radians;
};

//--------------------------------------------------------------------------------------------------

class Rotatable
{
public:
	virtual ~Rotatable() = 0;
	void SetRotation(float angle);
	void Rotate(float angle);

	const Angle& GetAngle() const;

protected:
	Angle m_Angle{};

	virtual void Refresh() {};
};

//--------------------------------------------------------------------------------------------------

inline Rotatable::~Rotatable()
{
}

//--------------------------------------------------------------------------------------------------

inline void Rotatable::SetRotation(float angle)
{
	m_Angle.degrees = angle;
	m_Angle.radians = float(angle * M_PI / 180);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Rotatable::Rotate(float angle)
{
	SetRotation(m_Angle.degrees + angle);
	if (m_Angle.degrees >= 360.f || m_Angle.degrees <= -360.f)
		SetRotation(0);
}

//--------------------------------------------------------------------------------------------------

inline const ::Angle& Rotatable::GetAngle() const
{
	return m_Angle;
}

//--------------------------------------------------------------------------------------------------

#endif
