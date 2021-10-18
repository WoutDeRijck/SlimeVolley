#ifndef GAME_REPLAY_H
#define GAME_REPLAY_H

#include <string>

#include "context.h"
#include "engine.h"
#include "system_eyes.h"
#include "system_points.h"
#include "system_render.h"
#include "system_replay.h"
#include "system_state_single.h"

class GameReplay
{
public:
	GameReplay(Context* _context, int _levelID, std::string _inputFile);
	~GameReplay();

	bool Run();

private:
	void Init();
	void AddSystems();
	void RemoveSystems();
	void MakeEntities();
	void DestroyEntities();

	int level;
	std::string inputFile;
	Context* context;
	Engine engine;
	SystemReplay srep;
	SystemEyes seyes;
	SystemPoints sp;
	SystemRender sr;
};

#endif