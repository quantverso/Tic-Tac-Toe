#ifndef QUANTVERSO_COMPONENT_H
#define QUANTVERSO_COMPONENT_H

//--------------------------------------------------------------------------------------------------

#include "Engine.h"
#include <list>

//--------------------------------------------------------------------------------------------------

class Entity;
class Collider;

//--------------------------------------------------------------------------------------------------

class Component
{
public:
	Component(Entity*& entity);
	virtual ~Component() = default;

protected:
	Entity* const entity; ///< Entidade proprietária do componente

	virtual void Draw() {};
	std::list<Collider*>& GetSceneColliders() const;

private:
	friend class Scene;

	virtual void Update() {};
};

//--------------------------------------------------------------------------------------------------

#endif
