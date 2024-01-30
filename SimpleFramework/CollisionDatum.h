#pragma once

#include "Entity.h"

struct CollisionDatum
{
	CollisionDatum(Entity one, Entity two);

	float overlap;
	Vec2 normal;
	Entity* entityOne;
	Entity* entityTwo;

	
};

CollisionDatum CreateCollisionDatum(Entity* entityOne, Entity* entityTwo) {

}