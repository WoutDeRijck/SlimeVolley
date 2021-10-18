#include "system_state_multi.h"

#include <set>

#include "component.h"
#include "component_player.h"
#include "component_motion.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"
#include "constants.h"

void SystemStateMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		Context* cont = engine->GetContext();
		// Is the level in freeze state?
		if (freeze_time == 0 && !cont->IsFrozen())
		{	
		
			// TODO: Check if the ball has dropped.
			// If so, freeze the game for 1.2 seconds and reset all velocities.
			// Determine the winner and
			// update the context accordingly.
			if (cspr_ball->y <= cspr_ball->y_min){
				cont->SetFrozen(true);
				freeze_time = cont->GetFps()*FREEZE_TIME; 		// frames / frames/second = 1.2
				if (cspr_ball->x < 373) {
					cont->IncreasePoints(2);
					cont->SetState(-(rand() % 3 + 8)); 	// -8, -9, -10
				}else{
					cont->IncreasePoints(1);
					cont->SetState(-(rand() % 3 + 5));	// -5, -6, -7
				}
				cmot_ball->v_x = 0;						// Reset all velocities
				cmot_ball->v_y = 0;
				cmot_player_1->v_x = 0;
				cmot_player_1->v_y = 0;
				cmot_player_2->v_x = 0;
				cmot_player_2->v_y = 0;
			}
		}
		else if (freeze_time != 0)
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context and wait
			// for	user input: spacebar to restart, ESC to quit (handled by
			// input system already). If the game is not finished yet, update
			// the context and reset player and ball positions.
			freeze_time -= 1;
			if(freeze_time == 0){
				if(cont->GetPoints(1) == 7) { 		// 1 won
					cont->SetState(-3);
				}else if(cont->GetPoints(2) == 7){	// 2 won
					cont->SetState(-4);
				}else if(cont->GetState() == -5||cont->GetState() == -6||cont->GetState() == -7){	//reset player and ball positions
					cspr_ball->x = SLIME_1_INIT_X;	// Serving position player 1
					cspr_ball->y = BALL_INIT_Y;
					cspr_player_1->x = SLIME_1_INIT_X;
					cspr_player_1->y = 0;
					cspr_player_2->x = SLIME_2_INIT_X;
					cspr_player_2->y = 0;
					cont->SetState(0);
					cont->SetFrozen(false);
				}else{
					cspr_ball->x = SLIME_2_INIT_X;	// Serving position player 2
					cspr_ball->y = BALL_INIT_Y;
					cspr_player_1->x = SLIME_1_INIT_X;
					cspr_player_1->y = 0;
					cspr_player_2->x = SLIME_2_INIT_X;
					cspr_player_2->y = 0;
					cont->SetState(0);
					cont->SetFrozen(false);
				}

			}			
		}
	}
}

bool SystemStateMulti::Initialize()
{
	// TODO: Initialize all component pointers (optional)
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
