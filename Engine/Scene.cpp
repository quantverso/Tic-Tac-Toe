#include "Scene.h"
#include "Engine.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------

Window& Scene::window{ Engine::window };
float&  Scene::deltaTime{ Engine::deltaTime };

// ------------------------------------------------------------------------------------------------

Scene::Scene() :
	m_SortObjectsRequest{},
	m_Viewport{ 0, 0,int(window.GetSize().width), int(window.GetSize().height) }
{
}

// ------------------------------------------------------------------------------------------------

Scene::~Scene()
{
	for (const auto& object : m_DestructibleObjects)
		delete object;
}

// ------------------------------------------------------------------------------------------------

void Scene::Draw()
{
	if (m_Texture)
		window.Draw(m_Texture.get());

	// Ordena os objetos com base na profundidade `depth`
	if (m_SortObjectsRequest)
	{
		m_Objects.sort([](Entity* a, Entity* b)
			{
				return a->transform.GetDepth() < b->transform.GetDepth();
			});
		m_SortObjectsRequest = false;
	}

	// Desenha objetos
	for (const auto& object : m_Objects)
		object->Draw();
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(Texture* texture)
{
	m_Texture = std::shared_ptr<Texture>(texture, [](Texture*) {});
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(const char* file)
{
	m_Texture = std::make_shared<Texture>();
	m_Texture->Load(file);
}

// ------------------------------------------------------------------------------------------------

void Scene::SetViewport(int x, int y, int width, int height)
{
	m_Viewport = { x, y, width, height };
}

// ------------------------------------------------------------------------------------------------

void Scene::AddObject(Entity* object, const char* id)
{
	object->m_Scene = this;
	object->m_RemovalRequest = false;

	if (id)
	{
		object->m_Id = id;
		m_ObjectMap[id] = object;
	}

	m_CreatedObjects.push_back(object);

	object->Awake();
}

// ------------------------------------------------------------------------------------------------

void Scene::UpdateObjects()
{
	// Inicializa objetos instanciados
	if (!m_CreatedObjects.empty())
	{
		std::vector<Entity*> mustBeStarted{ std::move(m_CreatedObjects) };
		m_CreatedObjects.clear();
		for (const auto& object : mustBeStarted)
		{
			object->Start();
			m_Objects.push_back(object);
		}
		SortObjects();
	}

	// Atualiza objetos
	for (auto it{ m_Objects.begin() }; it != m_Objects.end(); ++it)
	{
		Entity* object{ *it };

		object->Update();	

		// Atualiza os componentes do objeto
		for (const auto& [key, component] : object->m_Components)
			component->Update();

		// Se o objeto deve ser destruído ou removido é colocado na lista de remoção
		if (object->m_DestructionRequest || object->m_RemovalRequest)
			m_ObjectsToRemove.push_back(it);
	}
}

// ------------------------------------------------------------------------------------------------

void Scene::RemoveObjects()
{
	for (const auto& it : m_ObjectsToRemove)
	{
		Entity* object{ *it };

		if (auto it{ m_ObjectMap.find(object->GetId()) }; it != m_ObjectMap.end())
			m_ObjectMap.erase(it);

		if (object->m_DestructionRequest)
			delete object;

		m_Objects.erase(it);
	}

	m_ObjectsToRemove.clear();

	Sound::Release();
}

// ------------------------------------------------------------------------------------------------
