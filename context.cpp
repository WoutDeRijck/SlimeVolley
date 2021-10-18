#include "context.h"

int Context::GetScreenWidth()
{
	return screen_width;
}

int Context::GetScreenHeight()
{
	return screen_height;
}

double Context::GetFps()
{
	return fps;
};

void Context::UpdateStartTime()
{
	start_time = time(NULL);
}

time_t Context::GetStartTime()
{
	return start_time;
}

void Context::SetLevel(int _level)
{
	level = _level;
}

int Context::GetLevel()
{
	return level;
}

void Context::SetState(int _state)
{
	state = _state;
}

int Context::GetState()
{
	return state;
}

void Context::SetFrozen(bool _frozen)
{
	frozen = _frozen;
}

void Context::SwitchFrozen()
{
	frozen = !frozen;
}

bool Context::IsFrozen()
{
	return frozen;
}

void Context::SetPaused(bool _paused)
{
	paused = _paused;
}

void Context::SwitchPaused()
{
	paused = !paused;
}

bool Context::IsPaused()
{
	return paused;
}

void Context::SetReplay(bool _replay)
{
	replay = _replay;
}

bool Context::IsReplay()
{
	return replay;
}

void Context::SetInputFile(string _input_file)
{
	input_file = _input_file;
}

string Context::GetInputFile()
{
	return input_file;
}

void Context::UpdateScore(int _score)
{
	score += level * _score;
}

void Context::ResetScore()
{
	score = 0;
}

int Context::GetScore()
{
	return score;
}

void Context::IncreasePoints(int player)
{
	if (player == 1)
	{
		points_player_1 += 1;
	}
	else
	{
		points_player_2 += 1;
	}
}

void Context::ResetPoints()
{
	points_player_1 = 0;
	points_player_2 = 0;
}

int Context::GetPoints(int player)
{
	return player == 1 ? points_player_1 : points_player_2;
}

void Context::ToggleKey(int key, bool pressed)
{
	keys[key] = pressed;
}

bool Context::GetKeyPressed(int key, bool clear)
{
	bool pressed = false;
	if (keys.find(key) != keys.end())
	{
		pressed = keys.find(key)->second;
		if (clear)
		{
			keys[key] = false;
		}
	}
	return pressed;
}

void Context::Reset(int _state, bool _score)
{
	state = _state;
	frozen = false;
	paused = false;
	replay = false;
	if (_score)
	{
		score = 0;
	}
	points_player_1 = 0;
	points_player_2 = 0;
	keys.clear();
}
