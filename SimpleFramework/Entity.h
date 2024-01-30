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
public:

	Entity(Vec2 pos, float r);

	Vec2 position;
	
	Shape* shape;

	float radius;


	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

