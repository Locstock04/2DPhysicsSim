#pragma once

#include "Application.h"
#include "Entity.h"
#include "PhysicsObject.h"
#include "CollisionDatum.h"
#include "GUI.h"

class Lochiengine
{
private:
	std::vector<Entity*> entities;
	unsigned int collisionIterations = 20;

	float pullForce = 2.5f;

	// Allow the GUI to access private variables
	friend class GUI;
	GUI gui;
public:

	Lochiengine();
	~Lochiengine();
	Lochiengine(const Lochiengine& other) = delete;
	Lochiengine& operator=(const Lochiengine& other) = delete;

	// The delta value given to update should remain consistent and be unchanging. Variable time-rate has not been tested
	void Update(float delta);
	void MoveAllToward(Vec2 pos, float delta);
	void CreateDefaultEntity(Vec2 pos);

private:

	void Draw();
	void CollisionHandling();
};

