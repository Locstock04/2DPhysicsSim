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

	Entity(Vec2 _pos, Shape* _shape, PhysicsObject* _physicsObject);
	Entity(Vec2 _pos, ShapeType shapeType);
	Entity(Vec2 _pos, Shape* _shape);
	Entity(Vec2 _pos);
	~Entity();
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;


	Shape* shape;
	PhysicsObject* physicsObject;



	void Update(float delta);

	void Draw(LineRenderer* lines);
};

