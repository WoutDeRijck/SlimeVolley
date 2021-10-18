#include "system_render.h"

#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include <vector>

#include "color.h"
#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"
#include "tags.h"

using namespace std;

void SystemRender::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Clear screen and draw background
	Graphics::Instance().ClearScreen();
	Graphics::Instance().DrawBackground();

	// TODO: Iterate over all entities with the sprite component and print to
	// screen. For player slimes, draw the pupils as well.
	Context* cont = engine->GetContext();
	int level = cont->GetLevel();
	EntityStream* es = engine->GetEntityStream();
	set<Entity*> entities_sprite = es->WithTag(Component::SPRITE);
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);

	set<Entity*>::iterator itr;
	for(itr = entities_sprite.begin(); itr != entities_sprite.end(); itr++){	// Draw all sprites
		Component* comp = (*itr)->GetComponent(Component::SPRITE);
		ComponentSprite* comp_sprite = dynamic_cast<ComponentSprite*>(comp);
		Graphics::Instance().DrawBitmap(comp_sprite->sprite, comp_sprite->x, 299 - comp_sprite->y, comp_sprite->x_off, comp_sprite->y_off);
	}
	for(itr = entities_player.begin(); itr != entities_player.end(); itr++){ 	// Draw pupils
		Component* comp = (*itr)->GetComponent(Component::PLAYER);
		ComponentPlayer* comp_player = dynamic_cast<ComponentPlayer*>(comp);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_PUPIL, comp_player->pupil_x, 299 - comp_player->pupil_y, 5, 5);
	}
	
	Color c(0, 0, 0);
	// TODO: Use an appropriate color for the different backgrounds
	if (level == 2){
		c = Color(0, 128, 0);
	}else if(level == 3){
		c = Color(255, 255, 255);
	}

	// TODO: Print the current score if it is a singleplayer game
	if(level != 0){
		Graphics::Instance().DrawString(to_string(cont->GetScore()),375 ,10 ,c ,Graphics::ALIGN_CENTER);
	}
	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay
	int state = engine->GetContext()->GetState();
	if(cont->IsReplay()){
		Graphics::Instance().DrawString("Speed down (left), up (right) or zero (P)",30 ,325 ,c ,Graphics::ALIGN_LEFT);
		Graphics::Instance().DrawString("Next point (up), level (down) or quit (esc)",30 ,350 ,c ,Graphics::ALIGN_LEFT);
	}else{
		Graphics::Instance().DrawString("Press P to pause/unpause or ESC to quit",375 ,350 ,c ,Graphics::ALIGN_CENTER);
	}

	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)
	// A player won
	if(state == -1){
		Graphics::Instance().DrawString("You're on fire!",375 ,135 ,c ,Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press space to continue or ESC to quit",375 ,160 ,c ,Graphics::ALIGN_CENTER);
	}else if(state == -2){
		Graphics::Instance().DrawString("Get more practice soldier!",375 ,135 ,c ,Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press space to try again or ESC to quit",375 ,160 ,c ,Graphics::ALIGN_CENTER);
	}else if(state == -3){
		Graphics::Instance().DrawString("Player 1 kicked some butt!",375 ,135 ,c ,Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press space to restart or ESC to quit",375 ,160 ,c ,Graphics::ALIGN_CENTER);
	}else if(state == -4) {
		Graphics::Instance().DrawString("Congrats on beating player 1",375 ,135 ,c ,Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press space to restart or ESC to quit",375 ,160 ,c ,Graphics::ALIGN_CENTER);
	}else if (state == -5){	//Player_1
		if (cont->GetLevel() == 0){
			Graphics::Instance().DrawString ("Nice touch , Player 1!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics::Instance().DrawString ("Nice touch!", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}else if (state == -6){
		if (cont->GetLevel() == 0){
			Graphics::Instance().DrawString ("Well done , Player 1!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics::Instance().DrawString ("Well done", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}else if (state == -7){
		if (cont->GetLevel() == 0){
			Graphics :: Instance (). DrawString ("Cool, Player 1!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics :: Instance (). DrawString ("Cool!", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}else if (state == -8){	//Player_2
		if (cont->GetLevel() == 0){
			Graphics :: Instance (). DrawString ("You rock, Player 2!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics :: Instance (). DrawString ("You lost another point...", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}else if (state == -9){
		if (cont->GetLevel() == 0){
			Graphics :: Instance (). DrawString ("What a shot , Player 2!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics :: Instance (). DrawString ("Come on!", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}else if (state == -10){
		if (cont->GetLevel() == 0){
			Graphics :: Instance (). DrawString ("Awesome, Player 2!",375 , 310 , c, Graphics :: ALIGN_CENTER );
		}else{
			Graphics :: Instance (). DrawString ("You can do better!", 375 , 310 , c, Graphics :: ALIGN_CENTER );
		}
	}

	// Update current frame rate
	fps_accum++;
	t = al_get_time();
	if (t - fps_time >= 1)
	{
		fps = fps_accum;
		fps_accum = 0;
		fps_time = t;
	}
	Graphics::Instance().DrawString(to_string(fps), 375, 40, c, Graphics::ALIGN_CENTER);

	// Execute all draws
	Graphics::Instance().ExecuteDraws();
}

bool SystemRender::Initialize()
{
	int level = engine->GetContext()->GetLevel();
	// TODO: Set background according to level
	if(level == 1){
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND1);
	}else if(level == 2){
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND2);
	}else{
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND3);
	}
	return true;
}
