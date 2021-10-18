#include "system_ai.h"

#include <set>
#include <cmath>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "entity.h"
#include "engine.h"
#include "constants.h"

using namespace std;

void SystemAI::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Reset state and AI's decisions
	if (engine->GetContext()->GetState() != 0)
	{
		state = -1;
		Stop();
	}

	// Update AI's decisions if the game is not paused
	if (!engine->GetContext()->IsPaused())
	{
		UpdateKeys();
	}

	// Update player's movement
	UpdateMovement();
}

double SystemAI::XBallBelow(double y_target)
{
	// TODO: Calculate the value of x when y is first below y_target
	// x = x0 + v*t
	// y = y0 +vy0*t + 0.5*a*t²
	// Solve for t
	double vy = cmot_ball->v_y;
	double a = cmot_ball->a_y;
	double y0 = cspr_ball->y;
	double vx = cmot_ball->v_x;
	double t;

	t = (-sqrt(2*a*y_target-2*a*y0 + vy*vy) - vy)/a;

	return cspr_ball->x + vx*t;
}

void SystemAI::MoveLeft()
{
	pressed_left = true;
	pressed_right = false;
}

void SystemAI::MoveRight()
{
	pressed_left = false;
	pressed_right = true;
}

void SystemAI::Jump()
{
	pressed_up = true;
}

void SystemAI::Stop()
{
	pressed_left = false;
	pressed_right = false;
	pressed_up = false;
}

float SystemAI::GetRandom()
{
	return (float)rand() / (RAND_MAX);
}

void SystemAI::UpdateKeys()
{
	int level = engine->GetContext()->GetLevel();

	// TODO: Implement game logic for different levels
	if (level == 1)
	{
		// If ball is on left side of the net, set state equal to -1
		if(cspr_ball->x <= NET_POS_X){
			state = -1;
		}
		// If state equals 0 or the ball is in serving position (v_x = 0, x == 600)
		//    Set state equal to 0 and serve only if the ball drops below y = 110 by simply moving right and jump
		//    Return
		if(state == 0 || (cspr_ball->x == 600 && cmot_ball->v_x == 0)){
			state = 0;
			if(cspr_ball->y <= 110){
				MoveRight();
				Jump();
			}
			return;
		}
		
		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		double P = XBallBelow(90);
		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 600 (i.e. use abs(x - 600) < 6) by moving left/right (otherwise just stop)
		//    Return
		if(P <= NET_POS_X - 30){
			if(abs(cspr_player_2->x - 600) > 6){
				if(cspr_player_2->x < 600){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				Stop();
			}
			return;
		}
		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150
		//        Jump
		//    Return
		if(abs(P - cspr_player_2->x) < 25 && cspr_player_2->y <= 1){
			if(cspr_player_2->x >= 675 && cspr_ball->x > 625){
				Jump();
			}
			if(cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(P - cspr_player_2->x) < 75){
				Jump(); 
			}
			if(abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150){
				Jump();
			}
			return;
		}else if(cspr_player_2->y <= 1){	//    Position it as close as possible to P (use abs limit 25 instead of 6)
			if(abs(cspr_player_2->x - P) > 25){
				if(cspr_player_2->x < P){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				if(cspr_player_2->x < P){
					MoveLeft();
				}else{
					MoveRight();
				}
			}
		}else if(cspr_player_2->x >= 675){	//    Move right
			MoveLeft();
		}else{	//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
			if(abs(cspr_player_2->x - cspr_ball->x) > 25){
				if(cspr_player_2->x < cspr_ball->x){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				if(cspr_player_2->x < P){
					MoveLeft();
				}else{
					MoveRight();
				}
			}
		}
		
	}
	else if (level == 2)
	{
		// If ball is on left side of the net, set state equal to -1
		if(cspr_ball->x <= NET_POS_X){
			state = -1;
		}
		// If state does not equal -1 or the ball is in serving position (v_x = 0, x == 600)
		if(state != 1|| (cspr_ball->x == 600 && cmot_ball->v_x == 0)){
		//    If state equals -1
		//        Randomly set the state equal to 0, 1 or 2
			if(state == -1){
				state = rand() % 3;
			}
		//    If state equals 0
		//        If the ball drops below y = 75, move right and jump
			if(state == 0){
				if(cspr_ball->y <= 75){
					MoveRight();
					Jump();
				}
			}
		//    If state equals 1
		//        If the ball drops below y = 75, move left and jump
			if(state == 1){
				if(cspr_ball->y <= 75){
					MoveLeft();
					Jump();
				}
			}
		//    If state equals 2
			if(state == 2){
		//        If the ball's vertical speed is higher than 4.5 and slime's x < 645
		//            Move right (until slime's x >= 645)
				if(cmot_ball->v_y > 4.5 && cspr_player_2->x < 645){
					MoveRight();
				}
		//        If slime's x >= 645
		//            Stop
				if(cspr_player_2->x >= 645){
					Stop();
				}
		//        If the ball's vertical speed equals -1.125 and slime's x != 600
		//            Jump
				if(cmot_ball->v_y == -1.125 && cspr_player_2->x != 600){
					Jump();
				}
		//        If the ball's vertical speeds is lower than -4.5 and the slime is mid-air and slime's x >= 633
		//            Move left
				if(cmot_ball->v_y < -4.5 && cspr_player_2->x >= 633 && cspr_player_2->y >= 1){
					MoveLeft();
				}
			}
			return;
		}
		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		double P = XBallBelow(90);

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 480 (i.e. use abs(x - 480) < 6) by moving left/right (otherwise just stop)
		//    Return
		if(P <= NET_POS_X){
			if(abs(cspr_player_2->x - 480) > 6){
				if(cspr_player_2->x < P){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				Stop();
			}
			return;
		}

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150 and random value < 0.5
		//        Jump
		//    Return
		if(abs(P - cspr_player_2->x) < 25){
			if(cspr_player_2->x >= 675 && cspr_ball->x > 625){
				Jump();
			}
			if(cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(cspr_ball->x - cspr_player_2->x) < 75){
				Jump();
			}
			if(abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150 && GetRandom() < 0.5){
				Jump();
			}
			return;
		}else if(cspr_player_2->y <= 1){
			if(abs(cspr_player_2->x - P) > 25){
				if(cspr_player_2->x < P){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				if(cspr_player_2->x < P){
					MoveLeft();
				}else{
					MoveRight();
				}
			}
		}else if(cspr_player_2->x >= 675){
			MoveLeft();
		}else{
			if(abs(cspr_player_2->x - cspr_ball->x) > 25){
				if(cspr_player_2->x < cspr_ball->x){
					MoveRight();
				}else{
					MoveLeft();
				}
			}else{
				if(cspr_player_2->x < cspr_ball->x){
					MoveLeft();
				}else{
					MoveRight();
				}
			}
		}

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)

		// Else if the slime's x >= 675
		//    Move right

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
	}
	else if (level == 3)
	{
		MoveRight();
	}
}

void SystemAI::UpdateMovement()
{
	// TODO: Change player's movement according to AI decisions (i.e. pressed_xxx)
	cmot_player_2->v_x = 0;
	if(pressed_up && cspr_player_2->y <= 3){
		cmot_player_2->v_y = SLIME_V_Y;
		pressed_up = false;
	}
	if(pressed_right){
		cmot_player_2->v_x = SLIME_V_X;
		pressed_right = false;
	}
	if(pressed_left){
		cmot_player_2->v_x = -SLIME_V_X;
		pressed_left = false;
	}
}

bool SystemAI::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	EntityStream* es = engine->GetEntityStream();
	
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	set<Entity*> entity_ball = es->WithTag(Component::BALL);
	
	set<Entity*>::iterator itr;
	itr = entities_player.begin();
	cspr_player_1 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	itr++;
	cspr_player_2 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	cmot_player_2 = dynamic_cast<ComponentMotion*>((*itr)->GetComponent(Component::MOTION));
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	cmot_ball = dynamic_cast<ComponentMotion*>((*entity_ball.begin())->GetComponent(Component::MOTION));
	return true;
}
