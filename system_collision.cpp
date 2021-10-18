#define NOMINMAX

#include "system_collision.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <math.h>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"

using namespace std;

void SystemCollision::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Handle all possible collisions

		//Wall_PLayer1
		this->HandlePlayerWallCollision(cspr_player_1, cmot_player_1);

		//Ball_Player1
		this->HandleBallPlayerCollision(cspr_player_1, cmot_player_1);

		//Wall_Player2
		this->HandlePlayerWallCollision(cspr_player_2, cmot_player_2);

		//Ball_Player2
		this->HandleBallPlayerCollision(cspr_player_2, cmot_player_2);
		
		//Ball in game
		this->HandleBallWallCollision();

		//Ball_Net
		this->HandleBallNetCollision();
	}
		
}

void SystemCollision::HandleBallWallCollision(){
	// TODO: Handle a possible collision between the ball and a wall
	if (cspr_ball->x - cspr_ball->x_off <= cspr_ball->x_min || cspr_ball->x + cspr_ball->x_off >= cspr_ball->x_max){
		/* Switch direction x-velocity */
		cmot_ball->v_x *= -1;
	}
}

void SystemCollision::HandleBallNetCollision(){
	// TODO: Handle a possible collision between the ball and the net
	double distance_BN_x = sqrt((cspr_ball->x - 373)*(cspr_ball->x - 373));
	double distance_BN_y = sqrt((cspr_ball->y - 39)*(cspr_ball->y - 39));
	if (distance_BN_x <= cspr_ball->x_off && distance_BN_y <= cspr_ball->y_off){
		if (cspr_ball->x == 373){												/* Top */
			cmot_ball->v_y *= -1;
		}else{
			cmot_ball->v_x *= -1; 
		}
	}else if(distance_BN_x <= cspr_ball->x_off && cspr_ball->y < 39){			/* Sideways */
		cmot_ball->v_x *= -1;
	}

}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	// TODO: Handle a possible collision between a player and the walls/floor
	//Touches wall
	if(csprPlayer->x <= csprPlayer->x_min){
		csprPlayer->x = csprPlayer->x_min;
		cmotPlayer->v_x = 0;
	}
	if(csprPlayer->x >= csprPlayer->x_max){
		csprPlayer->x = csprPlayer->x_max;
		cmotPlayer->v_x = 0;
	}
	//Touches floor
	if (csprPlayer->y <= csprPlayer->y_min){
		cmotPlayer->v_y = 0;
	}
}

void SystemCollision::HandleBallPlayerCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	double d_x = cspr_ball->x - csprPlayer->x;
	double d_y = cspr_ball->y - csprPlayer->y;
	double dist = std::sqrt(d_x * d_x + d_y * d_y);
	if (d_y > 0 && dist < 46.875)
	{
		cspr_ball->x = csprPlayer->x + 46.875 * d_x / dist;
		cspr_ball->y = csprPlayer->y + 46.875 * d_y / dist;
		double d_v_x = cmot_ball->v_x - cmotPlayer->v_x;
		double d_v_y = cmot_ball->v_y - cmotPlayer->v_y;
		double s = (d_x * d_v_x + d_y * d_v_y * 2) / dist;
		if (s < 0)
		{
			cmot_ball->v_x += cmotPlayer->v_x - 2 * d_x * s / dist;
			cmot_ball->v_y += cmotPlayer->v_y - d_y * s / dist;
			cmot_ball->v_x = std::max(cmot_ball->v_x, -11.25);
			cmot_ball->v_x = std::min(cmot_ball->v_x, 11.25);
			cmot_ball->v_y = std::max(cmot_ball->v_y, -8.25);
			cmot_ball->v_y = std::min(cmot_ball->v_y, 8.25);
		}
	}
}

bool SystemCollision::Initialize(){
	// TODO: Initialize all component pointers (optional)
	// cspr linken aan de juiste entiteit

	EntityStream* es = engine->GetEntityStream();
	
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	set<Entity*> entity_ball = es->WithTag(Component::BALL);


	set<Entity*>::iterator itr;
	itr = entities_player.begin();
	cspr_player_1 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	cmot_player_1 = dynamic_cast<ComponentMotion*>((*itr)->GetComponent(Component::MOTION));
	itr++;
	cspr_player_2 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	cmot_player_2 = dynamic_cast<ComponentMotion*>((*itr)->GetComponent(Component::MOTION));
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	cmot_ball = dynamic_cast<ComponentMotion*>((*entity_ball.begin())->GetComponent(Component::MOTION));
	return true;
}