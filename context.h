#ifndef CONTEXT_H
#define CONTEXT_H

#include <ctime>
#include <map>
#include <string>

#include "constants.h"

using namespace std;

class Context
{
public:
	Context(int _screen_width, int _screen_height) :
		screen_width(_screen_width),
		screen_height(_screen_height),
		fps(FPS),
		start_time(std::time(nullptr)),
		level(0),
		state(0),
		frozen(false),
		paused(false),
		replay(false),
		input_file(""),
		score(0),
		points_player_1(0),
		points_player_2(0)
	{
	};

	~Context()
	{
	};

	int GetScreenWidth();
	int GetScreenHeight();
	double GetFps();
	void UpdateStartTime();
	time_t GetStartTime();
	void SetLevel(int _level);
	int GetLevel();
	void SetState(int _state);
	int GetState();
	void SetFrozen(bool _frozen);
	void SwitchFrozen();
	bool IsFrozen();
	void SetPaused(bool _paused);
	void SwitchPaused();
	bool IsPaused();
	void SetReplay(bool _replay);
	bool IsReplay();
	void SetInputFile(std::string _input_file);
	string GetInputFile();
	void UpdateScore(int _score);
	void ResetScore();
	int GetScore();
	void IncreasePoints(int player);
	void ResetPoints();
	int GetPoints(int player);
	void ToggleKey(int key, bool pressed);
	bool GetKeyPressed(int key, bool clear);
	void Reset(int _state, bool _score);

private:
	int screen_width;
	int screen_height;
	double fps;
	time_t start_time;
	int level;
	int state;
	bool frozen;
	bool paused;
	bool replay;
	string input_file;
	int score;
	int points_player_1;
	int points_player_2;
	map <int, bool> keys;
};

#endif