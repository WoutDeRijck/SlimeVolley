#ifndef SYSTEM_OUTPUT_H
#define SYSTEM_OUTPUT_H

#include <list>

#include "component_sprite.h"
#include "system.h"

class SystemOutput : public System
{
public:
	SystemOutput() : System(), initialized(false)
	{
	};

	virtual ~SystemOutput()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_OUTPUT;
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

	bool initialized;
	time_t start_time;
	int level;
	std::list<coordinates> cs;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_player_2;
	ComponentSprite* cspr_ball;
};

#endif