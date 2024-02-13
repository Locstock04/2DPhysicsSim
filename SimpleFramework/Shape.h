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
	Shape();
	virtual void Draw(LineRenderer* lines) = 0;
	virtual ShapeType getType() const = 0;
};

struct Circle : Shape {
	float radius;
	Circle(float r);
	Circle(Entity* _parent, float r);
	virtual void Draw(LineRenderer* lines) override;
	virtual ShapeType getType() const override { return ShapeType::Circle; }
};

struct Box : Shape {
	float width;

	float height;

	Box(float _width, float _height);
	Box(Entity* _parent, float _width, float _height);

	virtual void Draw(LineRenderer* lines) override;

	virtual ShapeType getType() const override { return ShapeType::Box; }

private:
	//Vec2 getTopLeft() const;
	//Vec2 getTopRight() const;
	//Vec2 getBottomLeft() const;
	//Vec2 getBottomRight() const;

};

struct GlobalShape : Shape {
	GlobalShape();
	GlobalShape(Entity* _parent);
};

struct Plane : GlobalShape {
	Vec2 normal;
	float displacement;

	Plane(Vec2 _normal, float _displacement);
	Plane(Entity* _parent, Vec2 _normal, float _displacement);
	virtual void Draw(LineRenderer* lines) override;

	virtual ShapeType getType() const override { return ShapeType::Plane; }

	Vec2 getTangent() const { return { normal.y, -normal.x }; };
};

struct Line : GlobalShape {
	Vec2 normal;
	float displacement;
	float thickness;

	Line(Vec2 _normal, float _displacement, float _thickness);
	Line(Entity* _parent, Vec2 _normal, float _displacement, float _thickness);

	virtual void Draw(LineRenderer* lines) override;

	virtual ShapeType getType() const override { return ShapeType::Line; }

};
