#include "Shape.h"

#include "Entity.h"

Shape::Shape(Entity* _parent)
{
	parent = _parent;
}



Circle::Circle(Entity* _parent, float r) : Shape(_parent)
{
	radius = r;
}

void Circle::Draw(LineRenderer* lines)
{
	lines->DrawCircle(parent->pos, radius);
}

