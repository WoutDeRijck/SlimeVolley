#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <vector>

#include "context.h"
#include "entity.h"
#include "entity_stream.h"
#include "system.h"

using namespace std;

class Engine
{
public:
	Engine(Context* _context) : context(_context)
	{
	};

	~Engine()
	{
	};

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void AddSystem(System* system);
	void RemoveSystem(System* system);
	void Update();
	vector<Entity*> GetEntities();
	Context* GetContext();
	EntityStream* GetEntityStream();

private:
	vector<Entity*> entities;
	vector<System*> systems;
	Context* context;
	EntityStream es;
};

#endif