#include "Transform.h"
#include "Scene.h"
#include "Entity.h"
#include "Collider.h"

//--------------------------------------------------------------------------------------------------

Transform::Transform(Entity* entity) :
	Component{ entity },
	m_Depth{},
	m_Collider{},
	m_PositionCollider{}
{
}

//--------------------------------------------------------------------------------------------------

void Transform::SetDepth(int depth)
{
	m_Depth = depth;
	entity->GetScene<>()->SortObjects();
}

//--------------------------------------------------------------------------------------------------
