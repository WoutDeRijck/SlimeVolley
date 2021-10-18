#include "engine.h"

#include <algorithm>

#include "allegro_lib.h"
#include "entity_stream.h"
#include "system.h"

using namespace std; 

void Engine::AddEntity(Entity* entity)
{
	entities.push_back(entity);
	es.EntityAdded(entity);
}

void Engine::RemoveEntity(Entity* entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	vector<Entity*>::iterator it = entities.begin();
	while (it != entities.end())
	{
		if ((*it) == entity)
		{
			it = entities.erase(it);
			es.EntityRemoved(entity);
		}
		else
		{
			it++;
		}
	}
}

void Engine::AddSystem(System* system)
{
	system->SetEngine(this);
	systems.push_back(system);
}

void Engine::RemoveSystem(System* system)
{
	vector<System*>::iterator it = systems.begin();
	while (it != systems.end())
	{
		if ((*it) == system)
		{
			system->SetEngine(NULL);
			it = systems.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Engine::Update()
{
	for (vector<System*>::iterator it = systems.begin(); it != systems.end(); it++)
	{
		(*it)->Update();
	}
}

vector<Entity*> Engine::GetEntities()
{
	return entities;
}

Context* Engine::GetContext()
{
	return context;
}

EntityStream * Engine::GetEntityStream()
{
	return &es;
}
