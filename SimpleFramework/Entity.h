#pragma once

#include "Maths.h"
#include "LineRenderer.h"


class Entity
{
public:

	Entity(Vec2 pos, float r);

	Vec2 position;

	float radius;


	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

