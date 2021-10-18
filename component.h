#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	enum Tag
	{
		SPRITE,
		MOTION,
		PLAYER,
		BALL,
		POINT
	};

	Component()
	{
	};

	virtual ~Component()
	{
	};

	virtual Tag GetTag() = 0;
};

#endif