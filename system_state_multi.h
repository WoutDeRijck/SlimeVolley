#ifndef SYSTEM_STATE_MULTI_H
#define SYSTEM_STATE_MULTI_H

#include "component_motion.h"
#include "component_sprite.h"
#include "system.h"

class SystemStateMulti : public System
{
public:
	SystemStateMulti() : System(), initialized(false), freeze_time(0), winner(0)
	{
	};

	virtual ~SystemStateMulti()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_STATE_MULTI;
	};

private:
	bool Initialize();

	bool initialized;
	int freeze_time;
	int winner;
	ComponentSprite* cspr_player_1;
	ComponentMotion* cmot_player_1;
	ComponentSprite* cspr_player_2;
	ComponentMotion* cmot_player_2;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
};

#endif