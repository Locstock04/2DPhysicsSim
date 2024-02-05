#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

Lochiengine::Lochiengine()
{

	Entity::gravity = Vec2(0, 0);
	
	entities.push_back(Entity({0, 0}, 1));
	entities.push_back(Entity({0, 0}, 1));



	//entities[0].acceleration = Vec2(5, 5);
	/*for (size_t i = 0; i < 50; i++)
	{
		entities.push_back(Entity(Vec2(0, 0), 1));

	}*/
}

void Lochiengine::Update(float delta)
{
	if (leftMouseDown) {
		//entities.push_back(Entity(cursorPos, 1));
	}

	if (rightMouseDown) {

		for (Entity& entity : entities)
		{
			entity.acceleration = /*glm::normalize*/(cursorPos - entity.position);
		}
	}
	else {
		for (Entity& entity : entities)
		{
			entity.acceleration = {0, 0};
		}
	}

	//entities[0].position = cursorPos;
	delta /= physicsIterations;

	for (size_t i = 0; i < physicsIterations; i++) {


		for (Entity& entity : entities)
		{
			entity.Update(delta);
		}
	}

	for (size_t i = 0; i < physicsIterations; i++)
	{

		CollisionHandling();

		for (Entity& entity : entities)
		{
			if (entity.position.x + entity.radius > borderRight) {
				Vec2 v = entity.getVelocity();
				v.x *= -1;
				entity.position.x = borderRight - entity.radius;
				entity.setVelocity(v * entity.VelocityKept);
			}
			else if (entity.position.x - entity.radius < borderLeft) {
				Vec2 v = entity.getVelocity();
				v.x *= -1;
				entity.position.x = borderLeft + entity.radius;
				entity.setVelocity(v * entity.VelocityKept);
			}

			if (entity.position.y + entity.radius > borderTop) {
				Vec2 v = entity.getVelocity();
				v.y *= -1;
				entity.position.y = borderTop - entity.radius;
				entity.setVelocity(v * entity.VelocityKept);
			}
			else if (entity.position.y - entity.radius < borderBottom) {
				Vec2 v = entity.getVelocity();
				v.y *= -1;

				//TODO: Set to correct offset and correct velocity ()
				//entity.position.y =  borderBottom - (entity.position.y - entity.radius - borderBottom) + 1;
				entity.position.y = borderBottom + entity.radius;
				entity.setVelocity(v * entity.VelocityKept);
			}
		}
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{
	entities.push_back(Entity(cursorPos, 1));

	std::cout << leftMouseDown << " " << cursorPos.x << ", " << cursorPos.y << "\n";
}

void Lochiengine::OnRightClick()
{
	std::cout << entities[0].getVelocity().x << ", " << entities[0].getVelocity().y << "\n";
}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity& entity : entities)
	{
		entity.Draw(lines);
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
			// Remove potential non touching circles 


			//if (rightMouseDown) {
			if (!(glm::abs(entities[i].position.x - entities[j].position.x) < entities[i].radius + entities[j].radius)) {
				continue;
			}
			else {
				if (!(glm::abs(entities[i].position.y - entities[j].position.y) < entities[i].radius + entities[j].radius)) {
					continue;
				}
			}
			//}



			CollisionDatum collisionDatum = CircleCircleCheck(&entities[i], &entities[j]);
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

