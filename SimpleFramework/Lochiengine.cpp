#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>

#include "imgui.h"


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
	if (rightMouseDown) {
		for (Entity* creatingEntity : entities)
		{
			// "accurate" gravity
			//float gravitionalConstant = 6.674 * glm::pow(10, -11);
			//float massOfCursor = 1000000000000;
			//float distanceFromMouse = glm::distance(creatingEntity->pos, cursorPos);
			//if (distanceFromMouse == 0.0f) { continue; }
			//Vec2 fromEntityToCursor = glm::normalize(cursorPos - creatingEntity->pos);
			//float acc = (gravitionalConstant * massOfCursor) / (distanceFromMouse * distanceFromMouse);
			//creatingEntity->physicsObject->setAcc(acc * fromEntityToCursor);

			creatingEntity->physicsObject->setAcc(2.5f * /*glm::normalize*/(cursorPos - creatingEntity->pos));
		}
	}
	else {
		for (Entity* creatingEntity : entities)
		{
			creatingEntity->physicsObject->setAcc({0, 0});
		}
	}

	for (Entity* creatingEntity : entities)
	{
		creatingEntity->Update(delta);
	}

	for (size_t i = 0; i < collisionIterations; i++)
	{
		CollisionHandling();
	}

	gui.Update(lines);
	Draw();
	
}

void Lochiengine::OnLeftClick()
{
	if (ImGui::GetIO().WantCaptureMouse) {
		return;
	}

	//entities.push_back(new Entity(cursorPos, new Circle(1)));
}

void Lochiengine::OnRightClick()
{
	if (!ImGui::GetIO().WantCaptureMouse) {
		return;
	}
}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity* creatingEntity : entities)
	{
		creatingEntity->Draw(lines);
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
