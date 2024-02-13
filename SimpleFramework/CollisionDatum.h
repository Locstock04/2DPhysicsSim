#pragma once

#include "Entity.h"

struct CollisionDatum
{
public:

	CollisionDatum(Entity* one, Entity* two);

	float overlap = -1;
	Vec2 normal;
	Entity* entityOne;
	Entity* entityTwo;

	void Solve();
};