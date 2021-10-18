#ifndef SYSTEM_AI_H
#define SYSTEM_AI_H

#include <time.h>

#include "component_motion.h"
#include "component_sprite.h"
#include "system.h"

class SystemAI : public System
{
public:
	SystemAI() : System(), initialized(false), state(-1), pressed_left(false), pressed_right(false), pressed_up(false)
	{
		srand((unsigned int)time(NULL));
	};

	~SystemAI()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_AI;
	};

private:
	bool Initialize();
	void UpdateKeys();
	void UpdateMovement();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Stop();
	float GetRandom();
	double XBallBelow(double y_target);

	bool initialized;
	int state;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_player_2;
	ComponentMotion* cmot_player_2;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
};

#endif