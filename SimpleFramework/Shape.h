#pragma once

#include "Maths.h"


class Entity;


enum class ShapeType {
	Circle,
	Box,
	Plane,
};

struct Shape {
public:
	Entity* parent = nullptr;
	Vec3 colour = { 1.f, 1.f, 1.f };
	Shape(Entity* _parent);
protected:
	//TODO: Ensure this is okay, similar to physics object base class
	Shape();
public:
	virtual void Draw() = 0;
	virtual ShapeType getType() const = 0;
};

struct Circle : Shape {
public:
	float radius;
	Circle(float r);
	Circle(Entity* _parent, float r);
	virtual void Draw() override;
	virtual ShapeType getType() const override { return ShapeType::Circle; }
};

struct Box : Shape {
private:

	float width;
	float height;

	float halfWidth;
	float halfHeight;

	float diagonal;
	float halfDiagonal;

public:
	void setWidth(float _width);
	void setHeight(float _height);
	float getWidth() const;
	float getHeight() const;

	float getHalfWidth() const;
	float getHalfHeight() const;

	void CalculateDiagonal();
	float getDiagonal() const;
	float getHalfDiagonal() const;

	float getTop() const;
	float getBottom() const;
	float getLeft() const;
	float getRight() const;



	Box(float _width, float _height);
	Box(Entity* _parent, float _width, float _height);


	virtual void Draw() override;


	virtual ShapeType getType() const override { return ShapeType::Box; }

private:
	//Vec2 getTopLeft() const;
	//Vec2 getTopRight() const;
	//Vec2 getBottomLeft() const;
	//Vec2 getBottomRight() const;

};


struct Plane : Shape {
	Vec2 normal;
	float displacement;

	Plane(Vec2 _normal, float _displacement);
	Plane(float angle, float _displacement);
	Plane(Entity* _parent, Vec2 _normal, float _displacement);
	virtual void Draw() override;

	virtual ShapeType getType() const override { return ShapeType::Plane; }

	Vec2 getTangent() const { return { normal.y, -normal.x }; };

	void setNormal(float degrees);
	void setNormal(Vec2 _normal);
	float getNormalDegrees() const;
};
