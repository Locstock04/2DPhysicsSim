#include <iostream>

#include "Lochiengine.h"

#include "CollisionFunctions.h"

Lochiengine::Lochiengine()
{
	entities.push_back(Entity(cursorPos, 1));
	entities[0].acceleration = Vec2(0, -10);
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

		//CollisionHandling();

		for (Entity& entity : entities)
		{
			if (entity.position.x + entity.radius > borderRight) {
				Vec2 v = entity.getVelocity();
				v.x *= - 1;
				entity.setVelocity(v);
				entity.position.x = borderRight;
			}
			if (entity.position.x - entity.radius < borderLeft) {
				Vec2 v = entity.getVelocity();
				v.x *= -1;
				entity.setVelocity(v);
				entity.position.x = borderLeft;
			}

			if (entity.position.y - entity.radius > borderTop) {
				//Vec2 v = entity.getVelocity();
				//v.y *= -1;
				//entity.position.y = borderTop;
				//entity.setVelocity(v);
			}
			if (entity.position.y - entity.radius - borderBottom < 0) {
				Vec2 v = entity.getVelocity();
				v.y *= -1;

				//TODO: Set to correct offset and correct velocity ()
				//entity.position.y =  borderBottom - (entity.position.y - entity.radius - borderBottom) + 1;
				entity.position.y = borderBottom + entity.radius;
				entity.setVelocity(v);

			}
		}
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{
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

