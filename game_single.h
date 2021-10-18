#ifndef GAME_SINGLE_H
#define GAME_SINGLE_H

#include "context.h"
#include "engine.h"
#include "system_ai.h"
#include "system_collision.h"
#include "system_eyes.h"
#include "system_input_single.h"
#include "system_motion.h"
#include "system_output.h"
#include "system_points.h"
#include "system_render.h"
#include "system_state_single.h"

class GameSingle
{
public:
	GameSingle(Context* _context, int _levelID);
	~GameSingle();

	int Run();

private:
	void Init();
	void AddSystems();
	void RemoveSystems();
	void MakeEntities();
	void DestroyEntities();

	int level;
	Context* context;
	Engine engine;
	SystemInputSingle sis;
	SystemAI sai;
	SystemMotion smot;
	SystemCollision scoll;
	SystemEyes seyes;
	SystemStateSingle sss;
	SystemPoints sp;
	SystemOutput so;
	SystemRender sr;
};

#endif