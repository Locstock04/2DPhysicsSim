#include <iostream>

#include "Lochiengine.h"

#include "CollisionFunctions.h"

Lochiengine::Lochiengine()
{
	entities.push_back(Entity(cursorPos, 1));
	entities.push_back(Entity(cursorPos, 1));
	entities[1].acceleration = Vec2(1000, 0);
	/*for (size_t i = 0; i < 50; i++)
	{
		entities.push_back(Entity(Vec2(0, 0), 1));

	}*/
}

void Lochiengine::Update(float delta)
{

	if (leftMouseDown) {
		entities.push_back(Entity(cursorPos, 1));
	}

	entities[0].position = cursorPos;

	for (Entity& entity : entities)
	{
		entity.Update(delta);
	}

	for (size_t i = 0; i < physicsIterations; i++)
	{
		CollisionHandling();
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{

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


			if (rightMouseDown) {


			if (!(glm::abs(entities[i].position.x - entities[j].position.x) < entities[i].radius + entities[j].radius)) {
				continue;
			}
			else {
				if (!(glm::abs(entities[i].position.y - entities[j].position.y) < entities[i].radius + entities[j].radius)) {
					continue;
				}
			}

			}
			//



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

