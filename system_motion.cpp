#define NOMINMAX

#include "system_motion.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

using namespace std;

void SystemMotion::Update()
{
	// Is the game running?
	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Update velocity and position of all entities with motion component (per frame?)
		EntityStream* es = engine->GetEntityStream();
		set<Entity*> entities_motion = es->WithTag(Component::MOTION);

		set<Entity*>::iterator itr;
		for(itr = entities_motion.begin(); itr != entities_motion.end(); itr++){
			Component* comp_m = (*itr)->GetComponent(Component::MOTION);
			Component* comp_s = (*itr)->GetComponent(Component::SPRITE);
			ComponentMotion* comp_motion = dynamic_cast<ComponentMotion*>(comp_m);
			ComponentSprite* comp_sprite = dynamic_cast<ComponentSprite*>(comp_s);

			comp_sprite->x += comp_motion->v_x;
			comp_sprite->y += comp_motion->v_y;
			comp_motion->v_x += comp_motion->a_x;
			comp_motion->v_y += comp_motion->a_y;
		}
	}
}
