#include "system_input_single.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputSingle::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		Initialize();
	}
	cmot_player_1->v_x = 0;
	// TODO: Change player's movement, pause and exit according to toggled
	// keys in context
	Context* cont = engine->GetContext();
	pressed_up = cont->GetKeyPressed(ALLEGRO_KEY_UP, true);
	if(pressed_up && cspr_player_1->y <= 3){
		cmot_player_1-> v_y = SLIME_V_Y;
	}
	pressed_left = cont->GetKeyPressed(ALLEGRO_KEY_LEFT, false);
	if(pressed_left){
		cmot_player_1-> v_x = -SLIME_V_X;
	}
	pressed_right = cont->GetKeyPressed(ALLEGRO_KEY_RIGHT, false);
	if(pressed_right){
		cmot_player_1-> v_x = SLIME_V_X;
	}
	pressed_p = cont->GetKeyPressed(ALLEGRO_KEY_P, true);
	if(pressed_p){
		cont->SwitchPaused();
	}
	pressed_esc = cont->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true);
	if(pressed_esc){
		cont->SetState(2);
		cont->ResetPoints();
		cont->ResetScore();
	}


	if(cont->GetState() == -1 || cont->GetState() == -2){
		pressed_spacebar = cont->GetKeyPressed(ALLEGRO_KEY_SPACE, true);
		if(pressed_spacebar){
			//try again or next level
			cont->ResetPoints();
			if(cont->GetState() == -1){
				cont->SetState(1);
			}else{
				cont->SetState(3);
			}
		}
	}

}

bool SystemInputSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	EntityStream* es = engine->GetEntityStream();
	
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	set<Entity*> entity_ball = es->WithTag(Component::BALL);
	
	cspr_player_1 = dynamic_cast<ComponentSprite*>((*entities_player.begin())->GetComponent(Component::SPRITE));
	cmot_player_1 = dynamic_cast<ComponentMotion*>((*entities_player.begin())->GetComponent(Component::MOTION));
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	cmot_ball = dynamic_cast<ComponentMotion*>((*entity_ball.begin())->GetComponent(Component::MOTION));

	return true;
}
