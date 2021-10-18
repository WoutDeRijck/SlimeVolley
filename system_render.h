#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include "entity.h"
#include "system.h"

class SystemRender : public System
{
public:
	SystemRender() : System(), initialized(false), fps(0), fps_accum(0), fps_time(0), t(0)
	{
		srand((unsigned int)time(NULL));
	};

	virtual ~SystemRender()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_RENDER;
	};

private:
	bool Initialize();

	bool initialized;
	int fps;
	int fps_accum;
	double fps_time;
	double t;
};

#endif
