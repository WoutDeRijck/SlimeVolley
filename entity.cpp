#include "entity.h"

#include <vector>

Entity* Entity::Add(Component* component)
{
	components[component->GetTag()] = component;
	return this;
}

Component* Entity::GetComponent(Component::Tag tag)
{
	return components[tag];
}

Component* Entity::Remove(Component* component)
{
	components.erase(component->GetTag());
	return component;
}

vector<Component::Tag> Entity::GetTags()
{
	vector<Component::Tag> v;
	for (ComponentMap::iterator it = components.begin(); it != components.end(); it++)
	{
		v.push_back(it->second->GetTag());
	}
	return v;
}

vector<Component*> Entity::GetComponents()
{
	vector<Component*> v;
	for (ComponentMap::iterator it = components.begin(); it != components.end(); it++)
	{
		v.push_back(it->second);
	}
	return v;
}
