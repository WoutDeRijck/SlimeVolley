#ifndef COMPONENT_PLAYER_H
#define COMPONENT_PLAYER_H

#include "component.h"
#include "constants.h"

class ComponentPlayer : public Component
{
public:
	int player_id;
	double radius, pupil_x, pupil_y;

	ComponentPlayer() : player_id(1), radius(RADIUS_SLIME), pupil_x(0), pupil_y(0)
	{
	};

	ComponentPlayer(int _player_id, double _radius) : player_id(_player_id), radius(_radius)
	{
	};

	virtual ~ComponentPlayer()
	{
	};

	virtual Tag GetTag()
	{
		return PLAYER;
	};
};

#endif