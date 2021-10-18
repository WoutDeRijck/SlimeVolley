#ifndef SYSTEM_INPUT_MULTI_H
#define SYSTEM_INPUT_MULTI_H

#include "component_motion.h"
#include "component_sprite.h"
#include "system.h"

class SystemInputMulti : public System
{
public:
	SystemInputMulti() : System(), initialized(false),pressed_spacebar(false), pressed_esc(false), pressed_a(false), pressed_d(false), pressed_w(false), pressed_left(false), pressed_right(false), pressed_up(false)
	{
	};

	virtual ~SystemInputMulti()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_INPUT_MULTI;
	};

private:
	bool Initialize();

	bool initialized;
	bool pressed_p;
	bool pressed_spacebar;
	bool pressed_esc;
	bool pressed_a;
	bool pressed_d;
	bool pressed_w;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentMotion* cmot_player_1;
	ComponentMotion* cmot_player_2;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_player_2;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
};

#endif