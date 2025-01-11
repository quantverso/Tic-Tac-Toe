#include "Component.h"
#include "Scene.h"
#include "Entity.h"
#include "Collider.h"

// ------------------------------------------------------------------------------------------------

Window& Component::window{ Engine::window }; ///< Referência para a janela gráfica

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	visible{},
	entity{ entity },
	scene{ entity->scene }
{	
}

//--------------------------------------------------------------------------------------------------

void Component::BindDependencies(Transform* transform)
{
	transform->PositionCollider = &Collider::Position;
	transform->sortObj = &scene->sortObj;
}

//--------------------------------------------------------------------------------------------------

void Component::BindDependencies(Collider* collider)
{
	collider->colliders = &scene->colliders;
	collider->OnCollision = &Entity::OnCollision;
	entity->transform.collider = collider;
}

//--------------------------------------------------------------------------------------------------
