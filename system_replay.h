#ifndef SYSTEM_REPLAY_H
#define SYSTEM_REPLAY_H

#include <list>

#include "component_sprite.h"
#include "system.h"

class SystemReplay : public System
{
public:
	SystemReplay() : System(), initialized(false), speed(1), status(-1), counter(0)
	{
		srand((unsigned int)time(NULL));
	};

	virtual ~SystemReplay()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_REPLAY;
	};

private:
	struct coordinates
	{
		double x_player_1;
		double y_player_1;
		double x_player_2;
		double y_player_2;
		double x_ball;
		double y_ball;
	};

	bool Initialize();
	void GoToNextFrame();
	void GoToNextPoint();
	void GoToNextLevel();

	bool initialized;
	double speed;
	int status;
	int counter;
	std::list<coordinates> cs;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_player_2;
	ComponentSprite* cspr_ball;
};

#endif