#include "Shape.h"

#include "Entity.h"

#include "DrawHandler.h"

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

void Circle::Draw()
{
	DrawHandler::DrawCircle(this);
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

void Box::Draw()
{
	DrawHandler::DrawBox(this);
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

void Plane::Draw()
{
	DrawHandler::DrawPlane(this);
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
