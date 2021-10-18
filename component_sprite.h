#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include "component.h"
#include "graphics.h"

class ComponentSprite : public Component
{
public:
	Graphics::Sprite sprite;
	double x, x_min, x_max, x_off;
	double y, y_min, y_max, y_off;

	ComponentSprite(Graphics::Sprite _sprite) : sprite(_sprite), x(0), x_min(0), x_max(0), x_off(0), y(0), y_min(0), y_max(0), y_off(0)
	{
	};

	ComponentSprite(Graphics::Sprite _sprite, double _x, double _y) : sprite(_sprite), x(_x), x_min(0), x_max(0), x_off(0), y(_y), y_min(0), y_max(0), y_off(0)
	{
	};

	ComponentSprite(Graphics::Sprite _sprite, double _x, double _x_min, double _x_max, double _x_off, double _y, double _y_min, double _y_max, double _y_off) : sprite(_sprite), x(_x), x_min(_x_min), x_max(_x_max), x_off(_x_off), y(_y), y_min(_y_min), y_max(_y_max), y_off(_y_off)
	{
	};

	virtual ~ComponentSprite()
	{
	};

	virtual Tag GetTag()
	{
		return SPRITE;
	};
};

#endif
