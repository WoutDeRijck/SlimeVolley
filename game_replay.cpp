#include "game_replay.h"

#include "allegro_lib.h"
#include "component_ball.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_point.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"

GameReplay::GameReplay(Context* _context, int _level, std::string _input_file) :
	level(_level),
	inputFile(_input_file),
	context(_context),
	engine(_context)
{
	context->SetLevel(level);
	AddSystems();
	MakeEntities();
};

GameReplay::~GameReplay()
{
	RemoveSystems();
	DestroyEntities();
}

bool GameReplay::Run()
{
	// Set replay mode and input file in context
	context->SetReplay(true);
	context->SetInputFile(inputFile);

	// Initialize game loop
	AllegroLib::Instance().StartLoop();
	bool quit = AllegroLib::Instance().IsWindowClosed();

	// Enter game loop
	while (!quit && context->GetState() <= 0)
	{
		// Start Allegro iteration
		AllegroLib::Instance().StartIteration();

		// TODO: Get the current Allegro event
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();
		// TODO: If event key down, toggle key in context
		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			context->ToggleKey(event.keyboard.keycode, true);
		}
		// TODO: If event key up, untoggle key in context
		if(event.type == ALLEGRO_EVENT_KEY_UP){
			context->ToggleKey(event.keyboard.keycode, false);
		}
		// TODO: If event timer, update engine
		if(event.type == ALLEGRO_EVENT_TIMER){ 
			engine.Update();
		}

		// Update quit value
		quit = AllegroLib::Instance().IsWindowClosed();
	}

	// Reset replay mode in context
	context->SetReplay(false);

	// Reset game state in context and return
	bool state = context->GetState() == 1;
	context->SetState(0);
	context->SetFrozen(false);
	return state;
}

void GameReplay::AddSystems()
{
	// TODO: Add all systems to the engine
	engine.AddSystem(&srep);
	engine.AddSystem(&seyes);
	engine.AddSystem(&sp);
	engine.AddSystem(&sr);
}

void GameReplay::RemoveSystems()
{
	// TODO: Remove all systems from the engine
	engine.RemoveSystem(&srep);
	engine.RemoveSystem(&seyes);
	engine.RemoveSystem(&sp);
	engine.RemoveSystem(&sr);
}

void GameReplay::MakeEntities()
{
	// TODO: Initialize required entities and add them to the engine
	int point_dist = 42; //Distance between point sprites
	int level = engine.GetContext()->GetLevel();

	Entity* ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, SLIME_1_INIT_X, RADIUS_BALL, 749 - RADIUS_BALL, RADIUS_BALL, BALL_INIT_Y, RADIUS_BALL, 299 - RADIUS_BALL, RADIUS_BALL)); //Hier wordt y als in ons assenstelsel meegegeven
	ball->Add(new ComponentBall());
	ball->Add(new ComponentMotion(0, 0, BALL_A_X, BALL_A_Y));
	engine.AddEntity(ball);

	Entity* player1 = new Entity();
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, SLIME_1_INIT_X, 39, 334, 39, 0, 0, 259, 39));
	player1->Add(new ComponentPlayer());
	player1->Add(new ComponentMotion(0, 0, SLIME_A_X, SLIME_A_Y));
	engine.AddEntity(player1);

	Entity* player2 = new Entity();
	player2->Add(new ComponentPlayer(2, RADIUS_SLIME));
	player2->Add(new ComponentMotion(0, 0, SLIME_A_X, SLIME_A_Y));
	if(level == 1){
		player2->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT1, SLIME_2_INIT_X, 412, 710, 39, 0, 0, 259, 39));
	}else if(level == 2){
		player2->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT2, SLIME_2_INIT_X, 412, 710, 39, 0, 0, 259, 39));
	}else{
		player2->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT3, SLIME_2_INIT_X, 412, 710, 39, 0, 0, 259, 39));
	}
	engine.AddEntity(player2);


	Entity* point11 = new Entity();
	point11->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 0*point_dist, 279)); // Elk punt 42 uit elkaar
	point11->Add(new ComponentPoint(1, 1));
	engine.AddEntity(point11);

	Entity* point12 = new Entity();
	point12->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 1*point_dist, 279));
	point12->Add(new ComponentPoint(1, 2));	
	engine.AddEntity(point12);

	Entity* point13 = new Entity();
	point13->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 2*point_dist, 279));
	point13->Add(new ComponentPoint(1, 3));
	engine.AddEntity(point13);

	Entity* point14 = new Entity();
	point14->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 3*point_dist, 279));
	point14->Add(new ComponentPoint(1, 4));
	engine.AddEntity(point14);

	Entity* point15 = new Entity();
	point15->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 4*point_dist, 279));
	point15->Add(new ComponentPoint(1, 5));
	engine.AddEntity(point15);

	Entity* point16 = new Entity();
	point16->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 5*point_dist, 279));
	point16->Add(new ComponentPoint(1, 6));
	engine.AddEntity(point16);

	Entity* point17 = new Entity();
	point17->Add(new ComponentSprite(Graphics::SPRITE_POINT, 12 + 6*point_dist, 279));
	point17->Add(new ComponentPoint(1, 7));
	engine.AddEntity(point17);

	Entity* point21 = new Entity();
	point21->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721, 279));
	point21->Add(new ComponentPoint(2, 1));
	engine.AddEntity(point21);

	Entity* point22 = new Entity();
	point22->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 1*point_dist, 279));
	point22->Add(new ComponentPoint(2, 2));	
	engine.AddEntity(point22);
	
	Entity* point23 = new Entity();
	point23->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 2*point_dist, 279));
	point23->Add(new ComponentPoint(2, 3));
	engine.AddEntity(point23);

	Entity* point24 = new Entity();
	point24->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 3*point_dist, 279));
	point24->Add(new ComponentPoint(2, 4));
	engine.AddEntity(point24);

	Entity* point25 = new Entity();
	point25->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 4*point_dist, 279));
	point25->Add(new ComponentPoint(2, 5));
	engine.AddEntity(point25);

	Entity* point26 = new Entity();
	point26->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 5*point_dist, 279));
	point26->Add(new ComponentPoint(2, 6));
	engine.AddEntity(point26);

	Entity* point27 = new Entity();
	point27->Add(new ComponentSprite(Graphics::SPRITE_POINT, 721 - 6*point_dist, 279));
	point27->Add(new ComponentPoint(2, 7));
	engine.AddEntity(point27);

	Entity* net = new Entity();
	net->Add(new ComponentSprite(Graphics::SPRITE_NET, 373, 0, 0, 2, 39, 0, 0, 0));
	engine.AddEntity(net);
}

void GameReplay::DestroyEntities()
{
	// TODO: Remove and destroy all entities
	vector<Entity*> entities = engine.GetEntities();

	vector<Entity*>::iterator itr;
	vector<Component*>::iterator itr_comp;
	for (itr = entities.begin(); itr != entities.end(); itr++){
		engine.RemoveEntity((*itr));
		vector<Component*> components = (*itr)->GetComponents();
		for(itr_comp = components.begin(); itr_comp != components.end(); itr_comp++){
			delete((*itr_comp));
		}
		delete((*itr));
	}
}
