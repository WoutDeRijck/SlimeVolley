#ifndef SYSTEM_EYES_H
#define SYSTEM_EYES_H

#include "component_sprite.h"
#include "system.h"

class SystemEyes : public System
{
public:
	SystemEyes() : System(), initialized(false)
	{
	};

	virtual ~SystemEyes()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_EYES;
	};

private:
	bool Initialize();

	bool initialized;
	ComponentSprite* cspr_ball;

};

#endif