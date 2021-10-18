#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <vector>

#include "context.h"

class Game
{
public:
	Game(Context* _context);
	~Game();

	void Run();

private:
	void ViewHighscores();
	void StartSingleplayer();
	void StartMultiplayer();
	void StartReplay(int selected_item);

	Context* context;
	std::vector<int> highscores;
	std::vector<std::time_t> start_times;
};

#endif
