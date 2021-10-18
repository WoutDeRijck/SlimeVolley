#ifndef TAGS_H
#define TAGS_H

#include <set>

#include "component.h"

class Tags
{
public:

	Tags(Component::Tag tag)
	{
		v.insert(tag);
	}

	Tags And(Component::Tag tag)
	{
		v.insert(tag);
		return *this;
	}

	std::set<Component::Tag> List()
	{
		return v;
	}

private:
	std::set<Component::Tag> v;
};

#endif