#ifndef SYSTEM_H
#define SYSTEM_H

#include "context.h"

class Engine;

class System
{
public:
	enum Type
	{
		TYPE_INPUT_MULTI,
		TYPE_INPUT_SINGLE,
		TYPE_AI,
		TYPE_MOTION,
		TYPE_COLISION,
		TYPE_EYES,
		TYPE_OUTPUT,
		TYPE_POINTS,
		TYPE_STATE_MULTI,
		TYPE_STATE_SINGLE,
		TYPE_REPLAY,
		TYPE_RENDER
	};

	System()
	{
	};

	virtual ~System()
	{
	};

	virtual void Update() = 0;
	virtual Type GetType() = 0;

	void SetEngine(Engine* _engine)
	{
		engine = _engine;
	};

protected:
	Engine* engine;
};

#endif