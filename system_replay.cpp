#define NOMINMAX

#include "system_replay.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"
#include "constants.h"

using namespace std;

void SystemReplay::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}
	Context* cont = engine->GetContext();
	// TODO: According to toggled keys in context, either:
	//   [ARROW_LEFT] Decrease playout speed by factor 2
	if(cont->GetKeyPressed(ALLEGRO_KEY_LEFT,true)){
		if(speed >= 2){
			speed = speed/2;
		}
	}
	//	 [ARROW_RIGHT] Increase playout speed by factor 2
	if(cont->GetKeyPressed(ALLEGRO_KEY_RIGHT,true)){
		speed = speed*2;
	}
	//   [ARROW_UP] Go to next point
	if(cont->GetKeyPressed(ALLEGRO_KEY_UP,true)){
		GoToNextPoint();
	}
	//	 [ARROW_DOWN] Go to next level
	if(cont->GetKeyPressed(ALLEGRO_KEY_DOWN,true)){
		GoToNextLevel();
	}
	//	 [P] Pause playout
	if(cont->GetKeyPressed(ALLEGRO_KEY_P,true)){
		cont->SwitchPaused();
	}
	//	 [ESC] Return to menu
	if(cont->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true)){
		cont->SetState(2);
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// TODO: Go to the next frame(s), if necessary
		if(status < 2){
			GoToNextFrame();
		}else{
			if(cont->GetPoints(1) == 7){
				cont->ResetPoints();
				cont->SetState(1);
			}else{
				cont->ResetPoints();
				cont->SetState(2);
			}
		}
		
	}
}

void SystemReplay::GoToNextFrame()
{
	// TODO: Go to next frame by setting the new coordinates. Set state to:
	//   0 if a normal frame has been found
	//   1 if a frame has been found in which the ball has dropped
	//   2 if there are no coordinates left
	// and update the context whenever necessary.
	Context* cont = engine->GetContext();
	list<coordinates>::iterator itr;
	coordinates coord;
	itr = cs.begin();
	bool pointScored = false;
	advance(itr, counter);
	for(int i = 0; i<=speed; i++){
		itr++;
		counter++;
		coord = (*itr);
		if(itr == cs.end()){
			if(coord.x_ball <= NET_POS_X){
			cont->IncreasePoints(1);
			cont->UpdateScore(200);
			}else{
			cont->IncreasePoints(2);
			cont->UpdateScore(-100);
			}
			status = 2;
			return;
		}
		if(cspr_ball->y - 20 <= cspr_ball->y_min && coord.x_player_1 == SLIME_1_INIT_X && coord.y_ball == BALL_INIT_Y && coord.x_player_2 == SLIME_2_INIT_X){
			pointScored = true;
			if(coord.x_ball <= NET_POS_X){
				cont->IncreasePoints(1);
				cont->UpdateScore(200);
			}else{
				cont->IncreasePoints(2);
				cont->UpdateScore(-100);
			}
		}
		if(pointScored){
			status = 1;
		}else{
			status = 0;
		}
		cspr_ball->x = coord.x_ball;
		cspr_ball->y = coord.y_ball;
		cspr_player_1->x = coord.x_player_1;
		cspr_player_1->y = coord.y_player_1;
		cspr_player_2->x = coord.x_player_2;
		cspr_player_2->y = coord.y_player_2;
	}
}

void SystemReplay::GoToNextPoint()
{
	while (status < 1)
	{
		GoToNextFrame();
	}
}

void SystemReplay::GoToNextLevel()
{
	while (status < 2)
	{
		GoToNextFrame();
	}
}

bool SystemReplay::Initialize()
{
	// TODO: Read input coordinates from file and push to list
	Context* cont = engine->GetContext();
	coordinates coord;
	string file = cont->GetInputFile();
	ifstream infile;
	infile.open(file, ios::in);
	while(infile >> coord.x_player_1 >> coord.y_player_1 >> coord.x_player_2 >> coord.y_player_2 >> coord.x_ball >> coord.y_ball){
		cs.push_back(coord);
	}
	infile.close();
	// TODO: Initialize all component pointers (optional)
	EntityStream* es = engine->GetEntityStream();
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	set<Entity*> entity_ball = es->WithTag(Component::BALL);
	set<Entity*>::iterator itr;
	itr = entities_player.begin();
	cspr_player_1 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	itr++;
	cspr_player_2 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	return true;
}
