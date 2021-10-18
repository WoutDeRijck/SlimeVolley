#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include "component_motion.h"
#include "component_sprite.h"
#include "system.h"

class SystemCollision : public System
{
public:
	SystemCollision() : System(), initialized(false)
	{
	};

	virtual ~SystemCollision()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_COLISION;
	};

private:
	bool Initialize();
	void HandleBallPlayerCollision(ComponentSprite* cspr_player, ComponentMotion* cmot_player);
	void HandlePlayerWallCollision(ComponentSprite* cspr_player, ComponentMotion* cmot_player);
	void HandleBallWallCollision();
	void HandleBallNetCollision();

	bool initialized;
	ComponentSprite* cspr_player_1;
	ComponentMotion* cmot_player_1;
	ComponentSprite* cspr_player_2;
	ComponentMotion* cmot_player_2;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
};

#endif