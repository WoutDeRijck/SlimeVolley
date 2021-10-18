#ifndef COMPONENT_POINT_H
#define COMPONENT_POINT_H

#include "component.h"

class ComponentPoint : public Component
{
public:
	int player_id, point_id;

	ComponentPoint(int _player_id, int _point_id) : player_id(_player_id), point_id(_point_id)
	{
	};

	virtual ~ComponentPoint()
	{
	};

	virtual Tag GetTag()
	{
		return POINT;
	};
};

#endif