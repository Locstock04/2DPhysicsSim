#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>


Lochiengine::Lochiengine()
{
	Entity::gravity = Vec2(0, 0);
	
	entities.push_back(new Entity({ 0, 0 }, new Circle(0.5f)));
	//entities[0]->physicsObject->invMass = 0.0f;
	entities.push_back(new Entity({ 0, 0 }, new Box(2, 2)));
	int lineSides = 0;
	for (int i = 0; i < lineSides; i++)
	{
		entities.push_back(new Entity({ 0, 0 }, new Plane(float(i * (360 /lineSides)), -10)));
	}

	


	entities.push_back(new Entity({ 0, 0 }, new Plane(0, -10)));

	//entities.push_back(new Entity({ 0, 0 }, new Plane({ 1, 0 }, -10)));
	//entities.push_back(new Entity({ 0, 0 }, new Plane({ -1, 0 }, -10)));
	//entities.push_back(new Entity({ 0, 0 }, new Plane({ 0, 1 }, -10)));
	//entities.push_back(new Entity({ 0, 0 }, new Plane({ 0, -1 }, -10)));
	
	//entities.push_back(new Entity({0, 0}, ShapeType::Line));
	//entities.push_back(Entity({0, 0}, ShapeType::Circle));

	

	//entities[0].acceleration = Vec2(5, 5);
	/*for (size_t i = 0; i < 50; i++)
	{
		entities.push_back(Entity(Vec2(0, 0), 1));

	}*/

}

Lochiengine::~Lochiengine()
{
	delete CollisionDatum::emptyTemp;
}

void Lochiengine::Update(float delta)
{
	entities[0]->pos = cursorPos;
	if (rightMouseDown) {


		for (Entity* entity : entities)
		{
			if (entities[0] == entity) {
				//continue;
			}




			//float distanceFromMouse = glm::distance(entity->pos, cursorPos);
			//if (distanceFromMouse == 0.0f) { continue; }
			//Vec2 fromEntityToCursor = glm::normalize(cursorPos - entity->pos);
			//float acc = (gravitionalConstant * massOfCursor) / (distanceFromMouse * distanceFromMouse);
			//entity->physicsObject->setAcc(acc * fromEntityToCursor);



			entity->physicsObject->setAcc(2.5f * /*glm::normalize*/(cursorPos - entity->pos));
		}
	}
	else {
		for (Entity* entity : entities)
		{
			entity->physicsObject->setAcc({0, 0});
		}
	}

	//entities[0].position = cursorPos;
	//delta /= physicsIterations;

	for (Entity* entity : entities)
	{
		entity->Update(delta);
	}

	for (size_t i = 0; i < physicsIterations; i++)
	{
		CollisionHandling();
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{
	//entities.push_back(new Entity(cursorPos, ShapeType::Circle));
	entities.push_back(new Entity(cursorPos, ShapeType::Box));

}

void Lochiengine::OnRightClick()
{
	//entities[0]->physicsObject->AddImpulse(-cursorPos + entities[0]->pos);

}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity* entity : entities)
	{
		entity->Draw(lines);
	}
}

void Lochiengine::CollisionHandling()
{
	// Collision Detection

	std::vector<CollisionDatum> collisions;

	for (int i = 0; i < entities.size(); i++)
	{
		for (int j = i + 1; j < entities.size(); j++)
		{
			if (entities[i]->physicsObject->isStatic && entities[j]->physicsObject->isStatic) { continue; }
			// Remove potential non touching circles 


			// Bounding boxes
			//if (rightMouseDown) {
			/*if (!(glm::abs(entities[i].pos.x - entities[j].pos.x) < entities[i].radius + entities[j].radius)) {
				continue;
			}
			else {
				if (!(glm::abs(entities[i].pos.y - entities[j].pos.y) < entities[i].radius + entities[j].radius)) {
					continue;
				}
			}*/
			//}

			CollisionDatum collisionDatum = GetCollision(entities[i], entities[j]);
			if (collisionDatum.overlap < 0) {
				continue;
			}
			collisions.push_back(collisionDatum);
		}
	}

	// Collision Response

	for (auto i = collisions.begin(); i != collisions.end(); i++)
	{
		i->Solve();
	}
}

