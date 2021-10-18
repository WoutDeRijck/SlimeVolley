#ifndef COMPONENT_BALL_H
#define COMPONENT_BALL_H

#include "component.h"

class ComponentBall : public Component
{
public:
	ComponentBall()
	{
	};

	virtual ~ComponentBall()
	{
	};

	virtual Tag GetTag()
	{
		return BALL;
	};
};

#endif