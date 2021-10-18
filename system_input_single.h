#ifndef SYSTEM_INPUT_SINGLE_H
#define SYSTEM_INPUT_SINGLE_H

#include "component_motion.h"
#include "system.h"
#include "component_sprite.h"

class SystemInputSingle : public System
{
public:
	SystemInputSingle() : System(), initialized(false), pressed_left(false), pressed_right(false), pressed_up(false)
	{
	};

	virtual ~SystemInputSingle()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_INPUT_SINGLE;
	};

private:
	bool Initialize();

	bool initialized;
	bool pressed_spacebar;
	bool pressed_esc;
	bool pressed_p;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentMotion* cmot_player_1;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
};

#endif