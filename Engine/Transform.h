#ifndef QUANTVERSO_TRANSFORM_H
#define QUANTVERSO_TRANSFORM_H

//--------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Rotatable.h"
#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

class Transform : public Component, public Rotatable, public Rectangle
{
public:
	Transform(Entity* entity);

	void SetDepth(int depth);
	const int& GetDepth() const;

private:
	friend class Collider;

	int		  m_Depth;
	Collider* m_Collider;

	void (Collider::* m_PositionCollider)(float x, float y);

	void Refresh();
};

//--------------------------------------------------------------------------------------------------

inline const int& Transform::GetDepth() const
{
	return m_Depth;
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Refresh()
{
	Rectangle::Refresh();
	if (m_Collider)
		(m_Collider->*m_PositionCollider)(float(x), float(y));
}

//--------------------------------------------------------------------------------------------------

#endif
