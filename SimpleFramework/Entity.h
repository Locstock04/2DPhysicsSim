#pragma once

#include "Maths.h"
#include "LineRenderer.h"

struct Shape {

};

struct Circle : Shape {
	float radius;
};

class Entity
{
private:

	void VerletUpdate(float delta);


public:

	static Vec2 gravity;
	const float VelocityKept = 1.0f;
	Entity(Vec2 pos, float r);

	Vec2 position = { 0, 0 };
	Vec2 old_position = {0, 0};
	Vec2 acceleration = { 0, 0 };

	Vec2 getVelocity();
	void setVelocity(Vec2 v);
	
	float invMass = 1;

	float radius;


	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

