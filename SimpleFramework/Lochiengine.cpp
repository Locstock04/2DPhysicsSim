#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>


Lochiengine::Lochiengine()
{
	Entity::gravity = Vec2(0, 0);
	
	//entities.push_back(new Entity({ 0, 0 }, ShapeType::Circle));
	//entities.push_back(new Entity({ 0, 0 }, ShapeType::Box));

	for (int i = 1; i < 1440; i++)
	{
		
		entities.push_back(new Entity({ 0, 0 }, new Plane(float(i/4), -10)));
		
	}

	entities.push_back(new Entity({ 0, 0 }, new Plane({ 0, 0 }, -10)));


	//entities.push_back(new Entity({ 0, 0 }, new Plane({ -3, -2 }, -10)));

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

	if (rightMouseDown) {


		for (Entity* entity : entities)
		{
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
	delta /= physicsIterations;

	for (size_t i = 0; i < physicsIterations; i++) {


		for (Entity* entity : entities)
		{
			entity->Update(delta);
		}
	}




	/*
	
	Velocity = prev - current
	Velocity + current = prev 
	prev = velocity + current
	
	
	*/




	for (size_t i = 0; i < physicsIterations; i++)
	{

		CollisionHandling();

		//TODO: Replace with planes
		//for (Entity* entity : entities)
		//{
		//	//switch (entity.shape->GetType())
		//	//{
		//		//case ShapeType::Circle:
		//	if (entity->shape->GetType() == ShapeType::Circle) {

		//		float radius = ((Circle*)entity->shape)->radius;
		//		if (entity->pos.x + radius > borderRight) {
		//			Vec2 v = entity->physicsObject->getVel();
		//			v.x *= -1;
		//			entity->pos.x = borderRight - radius;
		//			entity->physicsObject->setVel(v * entity->VelocityKept);
		//		}
		//		else if (entity->pos.x - radius < borderLeft) {
		//			Vec2 v = entity->physicsObject->getVel();
		//			v.x *= -1;
		//			entity->pos.x = borderLeft + radius;
		//			entity->physicsObject->setVel(v * entity->VelocityKept);
		//		}

		//		if (entity->pos.y + radius > borderTop) {
		//			Vec2 v = entity->physicsObject->getVel();
		//			v.y *= -1;
		//			entity->pos.y = borderTop - radius;
		//			entity->physicsObject->setVel(v * entity->VelocityKept);
		//		}
		//		else if (entity->pos.y - radius < borderBottom) {
		//			Vec2 v = entity->physicsObject->getVel();
		//			v.y *= -1;

		//			//TODO: Set to correct offset and correct velocity ()
		//			//entity.physicsObject->pos.y =  borderBottom - (entity.physicsObject->pos.y - radius - borderBottom) + 1;
		//			entity->pos.y = borderBottom + radius;
		//			entity->physicsObject->setVel(v * entity->VelocityKept);
		//		}
				//break;
				//default:
				//	break;
			//}
			
			
		//}
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{
	//entities.push_back(new Entity(cursorPos, ShapeType::Circle));
	entities.push_back(new Entity(cursorPos, ShapeType::Circle));

	std::cout << leftMouseDown << " " << cursorPos.x << ", " << cursorPos.y << "\n";
}

void Lochiengine::OnRightClick()
{
	//entities[0]->physicsObject->AddImpulse(-cursorPos + entities[0]->pos);

	std::cout << entities[0]->physicsObject->getVel().x << ", " << entities[0]->physicsObject->getVel().y << "\n";
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

			//if (entities[i]->physicsObject->isStatic() && entities[j]->physicsObject->isStatic()) { continue; }
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

