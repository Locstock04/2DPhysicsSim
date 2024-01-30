#include "Entity.h"

Entity::Entity(Vec2 pos, float r)
{
	position = pos;
	radius = r;
}

void Entity::Update(float delta)
{
}

void Entity::Draw(LineRenderer* lines)
{
	lines->DrawCircle(position, radius);
}
