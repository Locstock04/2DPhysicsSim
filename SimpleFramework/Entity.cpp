#include "Entity.h"

void Entity::VerletUpdate(float delta)
{
	Vec2 oldPos = old_position;
	position = position - old_position + acceleration * delta * delta;
	old_position = oldPos;
}

Entity::Entity(Vec2 pos, float r)
{
	position = pos;
	radius = r;
}

void Entity::Update(float delta)
{
	VerletUpdate(delta);
}

void Entity::Draw(LineRenderer* lines)
{
	lines->DrawCircle(position, radius);
}
