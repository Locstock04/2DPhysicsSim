#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>



Lochiengine::Lochiengine()
{
	gui.lochiengine = this;
	PhysicsObject::updatesPerSecond = 60.f;

	//entities[0]->physicsObject->AddImpulse({ 2, 2 });

}

Lochiengine::~Lochiengine()
{
	while (!entities.empty())
	{
		delete entities.back();
		entities.pop_back();
	}
}

void Lochiengine::Update(float delta)
{
	for (Entity* creatingEntity : entities)
	{
		creatingEntity->Update(delta);
	}

	for (size_t i = 0; i < collisionIterations; i++)
	{
		CollisionHandling();
	}

	gui.Update();
	Draw();

}

void Lochiengine::MoveAllToward(Vec2 pos, float delta)
{
	for (Entity* creatingEntity : entities)
	{
		creatingEntity->physicsObject->AddVelocity(delta * pullForce * (pos - creatingEntity->pos));
	}
}


void Lochiengine::CreateDefaultEntity(Vec2 pos)
{
	entities.push_back(new Entity(pos, new Circle(1)));
}


void Lochiengine::Draw()
{
	for (Entity* creatingEntity : entities)
	{
		creatingEntity->Draw();
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
			if (entities[i]->physicsObject->getType() == PhysicsObjectType::Static && entities[j]->physicsObject->getType() == PhysicsObjectType::Static) { continue; }
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
