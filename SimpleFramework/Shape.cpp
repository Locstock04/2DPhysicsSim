#include "Shape.h"

#include "Entity.h"

Shape::Shape(Entity* _parent) : parent(_parent)
{
}

Shape::Shape()
{
}



Circle::Circle(float r) :
	radius(r)
{
}

Circle::Circle(Entity* _parent, float r) : Shape(_parent),
	radius(r)
{
}

void Circle::Draw(LineRenderer* lines)
{
	lines->DrawCircle(parent->pos, radius);
}

Box::Box(float _width, float _height) :
	width(_width),
	height(_height)
{
}

Box::Box(Entity* _parent, float _width, float _height) : Shape(_parent),
	width(_width),
	height(_height)
{
}

void Box::Draw(LineRenderer* lines)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float left = parent->pos.x - halfWidth;
	float up = parent->pos.y - halfHeight;
	float right = parent->pos.x + halfWidth;
	float down = parent->pos.y + halfHeight;

	Vec2 topLeft(left, up);
	Vec2 topRight(right, up);
	Vec2 bottomLeft(left, down);
	Vec2 bottomRight(right, down);

	lines->DrawLineSegment(topLeft, topRight);
	lines->DrawLineSegment(topRight, bottomRight);
	lines->DrawLineSegment(bottomRight, bottomLeft);
	lines->DrawLineSegment(bottomLeft, topLeft);

	lines->DrawLineSegment(topLeft, bottomRight);
	lines->DrawLineSegment(topRight, bottomRight);


}

//Vec2 Box::getTopLeft() const
//{
//	return Vec2();
//}
//
//Vec2 Box::getTopRight() const
//{
//	return Vec2();
//}
//
//Vec2 Box::getBottomLeft() const
//{
//	return Vec2();
//}
//
//Vec2 Box::getBottomRight() const
//{
//	return Vec2();
//}

Plane::Plane(Vec2 _normal, float _displacement) :
	normal(glm::normalize(_normal)),
	displacement(_displacement)
{
}

Plane::Plane(Entity* _parent, Vec2 _normal, float _displacement) : GlobalShape(_parent),
	normal(_normal),
	displacement(_displacement)
{
}

void Plane::Draw(LineRenderer* lines)
{
	lines->DrawLineSegment(normal * displacement, normal * displacement + normal);

	Vec2 tangent(normal.y, -normal.x);
	lines->DrawLineSegment(normal * displacement + tangent * 2048.0f, normal * displacement - tangent * 2048.0f);
}

Line::Line(Vec2 _normal, float _displacement, float _thickness) :
	normal(_normal),
	displacement(_displacement),
	thickness(_thickness)
{
}

Line::Line(Entity* _parent, Vec2 _normal, float _displacement, float _thickness) : GlobalShape(_parent),
	normal(_normal),
	displacement(_displacement),
	thickness(_thickness)
{
}

void Line::Draw(LineRenderer* lines)
{

	lines->DrawLineSegment(normal * displacement, normal * displacement + normal);

	Vec2 tangent(normal.y, -normal.x);
	lines->DrawLineSegment(normal * (displacement + (thickness / 2)) + tangent * 2048.0f, normal * (displacement + (thickness / 2)) - tangent * 2048.0f);
	lines->DrawLineSegment(normal * (displacement - (thickness / 2)) + tangent * 2048.0f, normal * (displacement - (thickness / 2)) - tangent * 2048.0f);



}

GlobalShape::GlobalShape(Entity* _parent) : Shape(_parent)
{
}

GlobalShape::GlobalShape() : Shape()
{
}
