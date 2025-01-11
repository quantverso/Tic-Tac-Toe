#include "Transform.h"
#include "Collider.h"

//--------------------------------------------------------------------------------------------------

Transform::Transform(Entity* entity) :
	Component{ entity },
	depth{},
	sortObj{},
	collider{},
	PositionCollider{}
{
	BindDependencies(this);
}

//--------------------------------------------------------------------------------------------------
