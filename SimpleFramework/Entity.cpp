#include "Entity.h"

Vec2 Entity::gravity = Vec2(5.f, -10);


void Entity::Update(float delta)
{
	physicsObject->Update(delta);
}

void Entity::Draw(LineRenderer* lines)
{
	shape->Draw(lines);
}

Entity::Entity(Vec2 _pos, ShapeType shapeType) : 
	pos(_pos),
	physicsObject(new EulerObject(this))
{
	switch (shapeType)
	{
	case ShapeType::Circle:
		shape = new Circle(this, 1.f);
		break;
	case ShapeType::Box:
		shape = new Box(this, 1.f, 1.f);
		break;
	case ShapeType::Plane:
		shape = new Plane(this, { -1.f, 0.f }, -1);
		delete physicsObject;
		physicsObject = new StaticObject(this);
		break;
	case ShapeType::Line:
		shape = new Line(this, { 2.f, 0.f }, -1, 2);
		physicsObject = new StaticObject(this);
		break;
	default:
		shape = new Circle(this, 1.f);
		break;
	}
}

Entity::Entity(Vec2 _pos, Shape* _shape) :
	pos(_pos),
	physicsObject(new EulerObject(this)),
	shape(_shape)
{
	shape->parent = this;
	switch (shape->getType())
	{
	case ShapeType::Circle:
	case ShapeType::Box:
		break;
	case ShapeType::Plane:
	case ShapeType::Line:
		delete physicsObject;
		physicsObject = new StaticObject(this);
		break;
	default:
		throw;
		break;
	}
}

Entity::~Entity()
{
	delete physicsObject;
	delete shape;
}
