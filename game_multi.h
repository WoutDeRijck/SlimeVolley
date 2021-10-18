#ifndef GAME_MULTI_H
#define GAME_MULTI_H

#include "context.h"
#include "engine.h"
#include "system_collision.h"
#include "system_eyes.h"
#include "system_input_multi.h"
#include "system_motion.h"
#include "system_points.h"
#include "system_render.h"
#include "system_state_multi.h"

class GameMulti
{
public:
	GameMulti(Context* _context);
	~GameMulti();

	int Run();

private:
	void Init();
	void AddSystems();
	void RemoveSystems();
	void MakeEntities();
	void DestroyEntities();

	Context* context;
	Engine engine;
	SystemInputMulti sim;
	SystemMotion smot;
	SystemCollision scoll;
	SystemEyes seyes;
	SystemStateMulti ssm;
	SystemPoints sp;
	SystemRender sr;
};

#endif
