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
	lines->DrawCircle(parent->pos, radius, colour);
	lines->DrawCross(parent->pos, radius / sqrtf(2), colour);
}

Box::Box(float _width, float _height) :
	width(_width),
	height(_height),
	halfWidth(_width / 2),
	halfHeight(_height / 2)
{
	CalculateDiagonal();
}

Box::Box(Entity* _parent, float _width, float _height) : Shape(_parent), width(_width), height(_height),
	halfWidth(_width / 2),
	halfHeight(_height / 2)
{
	CalculateDiagonal();
}

void Box::Draw(LineRenderer* lines)
{
	Vec2 topLeft(getLeft(), getTop());
	Vec2 topRight(getRight(), getTop());
	Vec2 bottomLeft(getLeft(), getBottom());
	Vec2 bottomRight(getRight(), getBottom());

	lines->SetColour(colour);
	lines->AddPointToLine(topLeft);
	lines->AddPointToLine(topRight);
	lines->AddPointToLine(bottomRight);
	lines->AddPointToLine(bottomLeft);
	lines->FinishLineLoop();

	lines->DrawLineSegment(topLeft, bottomRight);
	lines->DrawLineSegment(topRight, bottomLeft);	
	//lines->SetColour({})
}

Plane::Plane(Vec2 _normal, float _displacement) :
	normal(glm::normalize(_normal)),
	displacement(_displacement)
{
	if (glm::isnan(normal.x)) {
		normal = { 1, 0 };
		//TODO: Put a error or something here
	}
}

Plane::Plane(float degrees, float _displacement) :
	normal(glm::normalize(Vec2(glm::cos(glm::radians(degrees)), glm::sin(glm::radians(degrees))))),
	displacement(_displacement)
{
}

Plane::Plane(Entity* _parent, Vec2 _normal, float _displacement) : Shape(_parent),
	normal(_normal),
	displacement(_displacement)
{
}

void Plane::Draw(LineRenderer* lines)
{
	lines->DrawLineSegment(normal * displacement - 2.f * normal, normal * displacement, colour);
	lines->DrawLineSegment(normal * displacement - normal + getTangent(), normal * displacement, colour);
	lines->DrawLineSegment(normal * displacement - normal - getTangent(), normal * displacement, colour);

	Vec2 tangent(normal.y, -normal.x);
	lines->DrawLineSegment(normal * displacement + tangent * 2048.0f, normal * displacement - tangent * 2048.0f, colour);
}

void Plane::setNormal(float degrees)
{
	normal = { glm::cos(glm::radians(degrees)), glm::sin(glm::radians(degrees)) };
}

void Plane::setNormal(Vec2 _normal)
{
	normal = _normal;
	if (glm::isnan(normal.x)) {
		normal = { 1, 0 };
		//TODO: Put a error or something here
	}
}

float Plane::getNormalDegrees() const
{
	float degrees = atan2f(normal.y, normal.x) * 180 / PI;
	if (degrees < 0) {
		degrees += 360;
	}
	return degrees;
}




void Box::setWidth(float _width)
{
	width = _width;
	halfWidth = width / 2;
	CalculateDiagonal();
}

void Box::setHeight(float _height)
{
	height = _height;
	halfHeight = height / 2;
	CalculateDiagonal();
}

float Box::getWidth() const
{
	return width;
}

float Box::getHeight() const
{
	return height;
}

float Box::getHalfWidth() const
{
	return halfWidth;
}

float Box::getHalfHeight() const
{
	return halfHeight;
}

void Box::CalculateDiagonal()
{
	diagonal = sqrtf(height * height + width * width);
	halfDiagonal = diagonal / 2;
}

float Box::getDiagonal() const
{
	return diagonal;
}

float Box::getHalfDiagonal() const
{
	return halfDiagonal;
}

float Box::getTop() const
{
	return parent->pos.y + getHalfHeight();
}

float Box::getBottom() const
{
	return parent->pos.y - getHalfHeight();
}

float Box::getLeft() const
{
	return parent->pos.x - getHalfWidth();
}

float Box::getRight() const
{
	return parent->pos.x + getHalfWidth();
}
