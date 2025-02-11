#include "Component.h"
#include "Scene.h"
#include "Entity.h"
#include "Collider.h"

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	entity{ entity }
{
}

//--------------------------------------------------------------------------------------------------

std::list<Collider*>& Component::GetSceneColliders() const
{
	return entity->GetScene<>()->m_Colliders;
};

//--------------------------------------------------------------------------------------------------
