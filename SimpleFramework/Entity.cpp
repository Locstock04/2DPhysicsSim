#include "Entity.h"

void Entity::VerletUpdate(float delta)
{
	Vec2 oldPos = position;
	position = (2.f *position) - old_position + (acceleration + gravity) * (delta * delta);
	old_position = oldPos;
}


Entity::Entity(Vec2 pos, float r)
{
	position = pos;
	old_position = pos;
	acceleration = { 0, 0 };
	radius = r;
}

Vec2 Entity::getVelocity()
{
	return position - old_position;
}

void Entity::setVelocity(Vec2 v)
{
	// v = pos - oldPos
	// oldPos = pos - v
	
	old_position = position - v;
}



void Entity::Update(float delta)
{
	VerletUpdate(delta);
}

void Entity::Draw(LineRenderer* lines)
{
	lines->DrawCircle(position, radius);
}
