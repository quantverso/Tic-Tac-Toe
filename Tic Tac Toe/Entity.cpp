#include "Entity.h"
#include "Engine.h"
#include "Scene.h"

// ------------------------------------------------------------------------------------------------

Window&		Entity::window{ Engine::window };		///< Janela gráfica
float&		Entity::deltaTime{ Engine::deltaTime };	///< Tempo decorrido entre frames

//--------------------------------------------------------------------------------------------------

Entity::Entity() :	
	id{ id_ },
	tag{ tag_ },	
	scene{ scene_ },
	scene_{},
	visible{ true },	
	material{ *AddComponent<Material>() },
	transform{ *AddComponent<Transform>() }
{
}

// ------------------------------------------------------------------------------------------------

Entity::~Entity()
{
	if (current && this == *(*current)) {
		objects->erase(*current);
		//*current = objects->begin();
	}
	else if (objects)
		objects->remove(this);
}

// ------------------------------------------------------------------------------------------------

void Entity::UpdateComponents()
{
	for (const auto& component : components)
		component.second->Update();
}

// ------------------------------------------------------------------------------------------------

void Entity::DrawComponents()
{
	for (const auto& component : components)
		if (component.second->visible)
			component.second->Draw();
}

// ------------------------------------------------------------------------------------------------
