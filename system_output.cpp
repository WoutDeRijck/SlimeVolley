#include "system_output.h"

#include <fstream>
#include <list>

#include "component_player.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"

using namespace std;

void SystemOutput::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}
	Context* cont = engine->GetContext();
	// TODO: Push back coordinates if they are different from last frame
	if(!cont->IsFrozen() && !cont->IsPaused()){
		coordinates coord;
		coord.x_player_1 = cspr_player_1->x;
		coord.x_player_2 = cspr_player_2->x;
		coord.y_player_1 = cspr_player_1->y;
		coord.y_player_2 = cspr_player_2->y;
		coord.x_ball = cspr_ball->x;
		coord.y_ball = cspr_ball->y;
		cs.push_back(coord);
	}
	// Is there a winner?
	if (engine->GetContext()->GetState() > 0)
	{
		// TODO: Output coordinates to file
		list<coordinates>::iterator itr;
		ofstream outfile;
		outfile.open("./assets/highscores/" + to_string(start_time) + "_" + to_string(level) + ".txt", ios_base::app);
		for(itr = cs.begin(); itr != cs.end(); itr++){
			outfile << (*itr).x_player_1 << "\t";
			outfile << (*itr).y_player_1 << "\t";
			outfile << (*itr).x_player_2 << "\t";
			outfile << (*itr).y_player_2 << "\t";
			outfile << (*itr).x_ball << "\t";
			outfile << (*itr).y_ball << "\n";
		}
		outfile.close();
	}
}

bool SystemOutput::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	Context* cont = engine->GetContext();
	EntityStream* es = engine->GetEntityStream();
	set<Entity*> entities_player = es->WithTag(Component::PLAYER);
	set<Entity*> entity_ball = es->WithTag(Component::BALL);
	set<Entity*>::iterator itr;
	itr = entities_player.begin();
	cspr_player_1 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	itr++;
	cspr_player_2 = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
	cspr_ball = dynamic_cast<ComponentSprite*>((*entity_ball.begin())->GetComponent(Component::SPRITE));
	level = cont->GetLevel();
	start_time = cont->GetStartTime();
	return true;
}
