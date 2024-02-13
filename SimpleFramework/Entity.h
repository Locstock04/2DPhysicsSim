#pragma once

#include "Maths.h"
#include "LineRenderer.h"
#include "Shape.h"
#include "PhysicsObject.h"


class PhysicsObject;

class Entity
{
private:


public:

	Vec2 pos;

	static Vec2 gravity;
	const float VelocityKept = 1.0f;
	Entity(Vec2 _pos, ShapeType shapeType);
	Entity(Vec2 _pos, Shape* _shape);
	~Entity();
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;


	Shape* shape;
	PhysicsObject* physicsObject;



	void Update(float delta);

	void Draw(LineRenderer* Lines);
};

