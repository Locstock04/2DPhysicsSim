#pragma once

#include "Maths.h"
#include "LineRenderer.h"



enum class ShapeType {
	Circle,
	Rectangle,
	Plane,
	Line,
};

struct Shape {
	virtual void Draw(LineRenderer* lines) = 0;
	virtual ShapeType GetType() const = 0;
};

struct Circle : Shape {
	float radius;
	virtual ShapeType GetType() const override { return ShapeType::Circle; }
};

struct Rectangle : Shape {
	float width;

	float height;

	virtual ShapeType GetType() const override { return ShapeType::Rectangle; }
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



class PhysicsObject {
	float invMass;

	virtual Vec2 getPos() {};
	virtual Vec2 getVel() {};
	virtual Vec2 getAcc() {};
	virtual Vec2 setPos() {};
	virtual Vec2 setVel() {};
	virtual Vec2 setAcc() {};

	virtual void Update(float delta) = 0;

};

class VerletObject : public PhysicsObject {
	void Update(float delta) override;
};

class EulerObject : public PhysicsObject {
	void Update(float delta) override;

};

class Entity
{
private:



public:

	static Vec2 gravity;
	const float VelocityKept = 1.0f;
	Entity(Vec2 pos, float r);

	Shape* shape;
	PhysicsObject* physicsObject;



	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

