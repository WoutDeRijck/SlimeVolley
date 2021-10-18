#include "system_eyes.h"

#include <cmath>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"
#include "constants.h"

void SystemEyes::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: Iterate over all player entities and set eyes in right position
	EntityStream* es = engine->GetEntityStream();
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	ComponentPlayer* cpl_player;
	ComponentSprite* cspr_player;
	double slope_player;
	double radius = 10.7157 - 5; // = Radius eyes(white) - radius pupil(estimate)


	set<Entity*>::iterator itr;
	for(itr = entities_player.begin(); itr != entities_player.end(); itr++){
		cpl_player = dynamic_cast<ComponentPlayer*>((*itr)->GetComponent(Component::PLAYER));
		cspr_player = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
		slope_player = (cspr_player->y - cspr_ball->y)/(cspr_player->x - cspr_ball->x);
		
		if(cpl_player->player_id == 1){
			if(cspr_player->x - cspr_ball->x == 0){
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_1);
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y);
			}else if((cspr_ball->x > cspr_player->x && cspr_ball->y <= cspr_player->y) || (cspr_ball->x > cspr_player->x && cspr_ball->y > cspr_player->y)){ //Kwadrant I or IV
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_1) + sqrt((radius*radius)/(1 + slope_player*slope_player));
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y) + slope_player*sqrt((radius*radius)/(1 + slope_player*slope_player));
			}else{	//Kwadrant II or III
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_1) - sqrt((radius*radius)/(1 + slope_player*slope_player));
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y) - slope_player*sqrt((radius*radius)/(1 + slope_player*slope_player));
			}
		}else{
			if(cspr_player->x - cspr_ball->x == 0){
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_2);
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y);
			}else if((cspr_ball->x > cspr_player->x && cspr_ball->y <= cspr_player->y) || (cspr_ball->x > cspr_player->x && cspr_ball->y > cspr_player->y)){ //Kwadrant I or IV
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_2) + sqrt((radius*radius)/(1 + slope_player*slope_player));
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y) + slope_player*sqrt((radius*radius)/(1 + slope_player*slope_player));
			}else{	//Kwadrant II or III
				cpl_player->pupil_x = (cspr_player->x+PUPILS_OFFSET_X_2) - sqrt((radius*radius)/(1 + slope_player*slope_player));
				cpl_player->pupil_y = (cspr_player->y+PUPILS_OFFSET_Y) - slope_player*sqrt((radius*radius)/(1 + slope_player*slope_player));
			}
		}
	
	
	}
}

bool SystemEyes::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	EntityStream* es = engine->GetEntityStream();
	set<Entity*> entity_ball = es->WithTag(Component::BALL);
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	return true;
}
