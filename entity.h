#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <vector>

#include "component.h"

using namespace std;

typedef map<Component::Tag, Component*> ComponentMap;

class Entity
{
public:
	Entity()
	{
	}

	~Entity()
	{
	}

	Entity* Add(Component* component);
	Component* Remove(Component* component);
	Component* GetComponent(Component::Tag tag);
	vector<Component*> GetComponents();
	vector<Component::Tag> GetTags();

private:
	ComponentMap components;
};

#endif
