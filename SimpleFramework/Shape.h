#pragma once

#include "LineRenderer.h"

#include "Maths.h"

class Entity;
class LineRender;


enum class ShapeType {
	Circle,
	Box,
	Plane,
	Line,
};

struct Shape {
	Entity* parent;
	Shape(Entity* _parent);
	virtual void Draw(LineRenderer* lines) = 0;
	virtual ShapeType GetType() const = 0;
};

struct Circle : Shape {
	float radius;
	Circle(Entity* _parent, float r);
	virtual void Draw(LineRenderer* lines) override;
	virtual ShapeType GetType() const override { return ShapeType::Circle; }
};

struct Rectangle : Shape {
	float width;

	float height;

	virtual ShapeType GetType() const override { return ShapeType::Box; }
};

struct GlobalShape : Shape {

};

struct Plane : GlobalShape {
	Vec2 normal;
	float displacement;
	virtual ShapeType GetType() const override { return ShapeType::Plane; }

};

struct Line : GlobalShape {
	Vec2 normal;
	float displacement;
	float thickness;
	virtual ShapeType GetType() const override { return ShapeType::Line; }

};
