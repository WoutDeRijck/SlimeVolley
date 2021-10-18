#include "system_points.h"

#include "component_point.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

void SystemPoints::Update()
{
	// TODO: Set the correct sprites of all entities with point component
	EntityStream* es = engine->GetEntityStream();
	Context* cont = engine->GetContext();
	ComponentPoint* cpoint;
	ComponentSprite* cspr;
	set<Entity*> entities_point = es->WithTag(Component::POINT);


	set<Entity*>::iterator itr;
	for(itr = entities_point.begin(); itr != entities_point.end(); itr++){
		cspr = dynamic_cast<ComponentSprite*>((*itr)->GetComponent(Component::SPRITE));
		cpoint = dynamic_cast<ComponentPoint*>((*itr)->GetComponent(Component::POINT));
		if(cpoint->point_id <= cont->GetPoints(1) && cpoint->player_id == 1){
			cspr->sprite = Graphics::SPRITE_POINT_P1;
		}else if(cpoint->point_id <= cont->GetPoints(2) && cpoint->player_id == 2){
			cspr->sprite = Graphics::SPRITE_POINT_P2;
		}else{
			cspr->sprite = Graphics::SPRITE_POINT;
		}
	}

}
