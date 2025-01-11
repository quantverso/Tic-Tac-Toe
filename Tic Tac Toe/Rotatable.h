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
	void Rotation(float angle);
	void Rotate(float angle);

	const ::Angle& Angle() const;

protected:
	::Angle angle{};

	virtual void Refresh() {};
};

//--------------------------------------------------------------------------------------------------

inline Rotatable::~Rotatable()
{
}

//--------------------------------------------------------------------------------------------------

inline void Rotatable::Rotation(float angle)
{
	this->angle.degrees = angle;
	this->angle.radians = float(angle * M_PI / 180);
	Refresh();
}

//--------------------------------------------------------------------------------------------------

inline void Rotatable::Rotate(float angle)
{
	Rotation(this->angle.degrees + angle);
	if (this->angle.degrees >= 360.f || this->angle.degrees <= -360.f)
		Rotation(0);
}

//--------------------------------------------------------------------------------------------------

inline const ::Angle& Rotatable::Angle() const
{
	return angle;
}

//--------------------------------------------------------------------------------------------------

#endif
