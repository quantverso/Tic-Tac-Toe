#include "Scene.h"
#include "Engine.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------

Window& Scene::window{ Engine::window };	   ///< Janela gráfica
float&  Scene::deltaTime{ Engine::deltaTime }; ///< Tempo decorrido entre frames

// ------------------------------------------------------------------------------------------------

Scene::Scene() :
	visible{ true },
	sortObj{},
	size{ window.Size() },
	viewport{ 0, 0, int(size.width), int(size.height) }
{
}

// ------------------------------------------------------------------------------------------------

Scene::~Scene()
{
	std::vector<Entity*> temp{ objects.begin(), objects.end() };
	for (const auto& obj : temp)
	{
		if (destroyable.find(obj) != destroyable.end())
			delete obj;
	}
	objects.clear();
}

// ------------------------------------------------------------------------------------------------

void Scene::AddObject(Entity* obj, const char* id)
{
	obj->scene_ = this;
	obj->objects = &objects;
	obj->current = &current;
	obj->destroy = &destroy;
	if (id)
	{
		obj->id_ = id;
		objHash[id] = obj;
	}
	created.push_back(obj);
	obj->Awake();
}

// ------------------------------------------------------------------------------------------------

void Scene::UpdateObjects()
{
	// Inicializa objetos instanciados
	if (!created.empty())
	{
		std::vector<Entity*> temp{ std::move(created) };
		created.clear();
		for (const auto& obj : temp)
		{
			obj->Start();
			objects.push_back(obj);
		}
		sortObj = true;
	}

	// Atualiza objetos
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		current = it;
		(*current)->Update();
		(*current)->UpdateComponents();
	}
}

// ------------------------------------------------------------------------------------------------

void Scene::Draw()
{
	window.SetViewport(&viewport);

	if(texture && visible)
		window.Draw(texture.get());

	// Ordena os objetos com base no valor da profundidade `depth`
	if (sortObj)
	{
		objects.sort([](Entity* a, Entity* b)
		{
			return a->transform.Depth() < b->transform.Depth();
		});
		sortObj = false;
	}

	// Desenha entidades
	for (const auto& obj : objects)
	{
		if (obj->visible)
			obj->Draw();

		obj->DrawComponents();
	}
}

// ------------------------------------------------------------------------------------------------

void Scene::DestroyObjects()
{
	for (const auto& obj : destroy)
	{
		delete obj;
	}
	destroy.clear();

	Sound::Release();
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(const Texture* texture)
{
	this->texture = std::shared_ptr<Texture>(const_cast<Texture*>(texture), [](Texture*) {});
}

// ------------------------------------------------------------------------------------------------

void Scene::SetViewport(int x, int y, int width, int height)
{
	size.width = float(width);
	size.height = float(height);
	viewport = Rect{ x, y, width, height };
}

// ------------------------------------------------------------------------------------------------

void Scene::SetBackground(const char* file)
{
	texture = std::make_unique<Texture>();
	texture->Load(file);
}

// ------------------------------------------------------------------------------------------------
