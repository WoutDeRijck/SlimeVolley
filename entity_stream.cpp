#include "entity_stream.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "component.h"

set<Entity*> EntityStream::WithTag(Component::Tag tag)
{
	return index[tag];
}

set<Entity*> EntityStream::WithTags(set<Component::Tag> tags)
{
	if (tags.size() == 1)
	{
		return WithTag(*tags.begin());
	}

	set<Entity*> comp;
	set<Entity*> output;
	set<Component::Tag>::iterator it = tags.begin();
	comp.insert(index[*it].begin(), index[*it].end());
	it++;
	while (it != tags.end())
	{
		Component::Tag tag = *it;
		if (index.count(tag) == 0)
		{
			return output;
		}
		set_intersection(comp.begin(), comp.end(), index[tag].begin(), index[tag].end(), inserter(output, output.begin()));
		comp.clear();
		comp.insert(output.begin(), output.end());
		output.clear();
		it++;
	}
	return comp;
}

void EntityStream::EntityAdded(Entity* entity)
{
	vector<Component::Tag> tags = entity->GetTags();
	for (vector<Component::Tag>::iterator it = tags.begin(); it != tags.end(); it++)
	{
		map<Component::Tag, set<Entity*>>::iterator got = index.find(*it);
		if (got != index.end())
		{
			got->second.insert(entity);
		}
		else
		{
			set<Entity*> tmp;
			tmp.insert(entity);
			index.insert(make_pair(*it, tmp));
		}
	}
}

void EntityStream::EntityRemoved(Entity* entity)
{
	map<Component::Tag, set<Entity*>>::iterator it = index.begin();
	while (it != index.end())
	{
		map<Component::Tag, set<Entity*>>::iterator got = index.find(it->first);
		if (got != index.end())
		{
			got->second.erase(entity);
		}
		it++;
	}
}
