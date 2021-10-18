#include "system_input_multi.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	
	// TODO: Change players' movement, pause and exit according to toggled
	// keys in context
	cmot_player_2->v_x = 0; // After keys were pressed, reset velocity
	cmot_player_1->v_x = 0; 
	Context* cont = engine->GetContext();

	
	pressed_a = cont->GetKeyPressed(ALLEGRO_KEY_A, false);
	if(pressed_a){
		cmot_player_1-> v_x = -SLIME_V_X;
	}
	pressed_d = cont->GetKeyPressed(ALLEGRO_KEY_D, false);
	if(pressed_d){
		cmot_player_1-> v_x = SLIME_V_X;
	}
	pressed_w = cont->GetKeyPressed(ALLEGRO_KEY_W, true);
	if(pressed_w && cspr_player_1->y <= 3){
		cmot_player_1-> v_y = SLIME_V_Y;
	}
	pressed_up = cont->GetKeyPressed(ALLEGRO_KEY_UP, true);
	if(pressed_up && cspr_player_2->y <= 3){
		cmot_player_2-> v_y = SLIME_V_Y;
	}
	pressed_left = cont->GetKeyPressed(ALLEGRO_KEY_LEFT, false);
	if(pressed_left){
		cmot_player_2-> v_x = -SLIME_V_X;
	}
	pressed_right = cont->GetKeyPressed(ALLEGRO_KEY_RIGHT, false);
	if(pressed_right){
		cmot_player_2-> v_x = SLIME_V_X;
	}
	pressed_p = cont->GetKeyPressed(ALLEGRO_KEY_P, true);
	if(pressed_p){
		cont->SwitchPaused();
	}
	pressed_esc = cont->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true);
	if(pressed_esc){
		cont->SetState(4);
		cont->ResetPoints();
	}

	if(cont->GetState() == -3 || cont->GetState() == -4){
		pressed_spacebar = cont->GetKeyPressed(ALLEGRO_KEY_SPACE, true);
		if(pressed_spacebar) {
			//restart
			cont->Reset(0, cont->GetScore());
			cspr_ball->x = SLIME_1_INIT_X;	// Serve position player 1
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

bool SystemInputMulti::Initialize()
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
