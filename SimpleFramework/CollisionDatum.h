#pragma once

#include "Entity.h"

struct CollisionDatum
{
public:

	CollisionDatum(PhysicsObject* one, PhysicsObject* two);

	float overlap = -1;
	Vec2 normal;
	PhysicsObject* objectOne;
	PhysicsObject* objectTwo;

	void Solve();

	static float elasticity;
};