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

Entity::Entity(Vec2 _pos, ShapeType shapeType)
{
	pos = _pos;
	physicsObject = new VerletObject(this);
	shape = new Circle(this, 1.f);
	/*switch (shapeType)
	{
	case ShapeType::Circle:
		shape = new Circle(this, 1.f);
		break;
	case ShapeType::Rectangle:
		break;
	case ShapeType::Plane:
		break;
	case ShapeType::Line:
		break;
	default:
		break;
	}*/
}

Entity::~Entity()
{
	//delete physicsObject;
	//delete shape;
}
