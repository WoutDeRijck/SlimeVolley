#ifndef COMPONENT_MOTION_H
#define COMPONENT_MOTION_H

#include "component.h"

class ComponentMotion : public Component
{
public:
	double v_x, v_y, a_x, a_y, j_y;

	ComponentMotion() : v_x(0.0), v_y(0.0), a_x(0.0), a_y(0.0), j_y(0.0)
	{
	};

	ComponentMotion(double _v_x, double _v_y, double _a_x, double _a_y) : v_x(_v_x), v_y(_v_y), a_x(_a_x), a_y(_a_y), j_y(0.0)
	{
	};

	virtual ~ComponentMotion()
	{
	};

	virtual Tag GetTag()
	{
		return MOTION;
	};
};

#endif