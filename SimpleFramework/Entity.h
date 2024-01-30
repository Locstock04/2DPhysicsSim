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

	Entity(Vec2 pos, float r);

	Vec2 position;
	Vec2 old_position;
	Vec2 acceleration;
	

	float radius;


	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

