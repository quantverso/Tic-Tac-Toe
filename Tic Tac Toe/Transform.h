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

	void Depth(int depth);
	const int& Depth() const;

private:
	friend class Entity;
	friend class Component;

	int		  depth;
	bool*	  sortObj;
	Collider* collider;

	void (Collider::* PositionCollider)(float x, float y);

	void Refresh();
};

//--------------------------------------------------------------------------------------------------

inline void Transform::Depth(int depth)
{
	depth = depth;
	*sortObj = true;
}

//--------------------------------------------------------------------------------------------------

inline const int& Transform::Depth() const
{
	return depth;
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Refresh()
{
	Rectangle::Refresh();
	if (collider)
		(collider->*PositionCollider)(float(x), float(y));
}

//--------------------------------------------------------------------------------------------------

#endif
