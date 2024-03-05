#pragma once

#include "Entity.h"

struct CollisionDatum
{
public:

	CollisionDatum(PhysicsObject* one, PhysicsObject* two);
	CollisionDatum();


	float overlap = -1;
	Vec2 normal;
	PhysicsObject* entityOne;
	PhysicsObject* entityTwo;

	void Solve();
};