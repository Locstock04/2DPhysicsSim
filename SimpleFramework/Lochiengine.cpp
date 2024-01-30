#include <iostream>

#include "Lochiengine.h"

#include "CollisionFunctions.h"

Lochiengine::Lochiengine()
{

}

void Lochiengine::Update(float delta)
{
	
	for (Entity& entity : entities)
	{
		entity.Update(delta);
	}

	Draw();
	
}

void Lochiengine::OnLeftClick()
{
	entities.push_back(Entity(cursorPos, 1));

}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity& entity : entities)
	{
		entity.Draw(lines);
	}
}

std::vector<CollisionDatum> Lochiengine::CollisionDetection()
{
	std::vector<CollisionDatum> collisions;

	for (int i = 0; i < entities.size(); i++)
	{
		for (int j = i + 1; j < entities.size(); j++)
		{
			if (CircleCircleCheck(entities[i], entities[j])) {
				
			}
		}
	}

	return collisions;
}


void Lochiengine::CollisionResponse()
{
	std::vector<CollisionDatum> collisions = CollisionDetection();
}
