#include "Entity.h"
#include "Engine.h"

// -----------------------------------------------------------------------------------------------

Window& Entity::window{ Engine::window };
float&  Entity::deltaTime{ Engine::deltaTime };

//-------------------------------------------------------------------------------------------------

Entity::Entity() :
	m_Tag{},
	m_Scene{},
	m_RemovalRequest{},
	m_DestructionRequest{},
	sprite{ *AddComponent<Sprite>() },
	transform{ *AddComponent<Transform>() }
{
}

// ------------------------------------------------------------------------------------------------

void Entity::SetTag(const char* tag)
{
	m_Tag = tag;
}

//-------------------------------------------------------------------------------------------------


void Entity::Remove()
{
	m_RemovalRequest = true;
}

// ------------------------------------------------------------------------------------------------

void Entity::Destroy()
{
	m_DestructionRequest = true;
}

// ------------------------------------------------------------------------------------------------
