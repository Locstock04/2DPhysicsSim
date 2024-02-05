#pragma once

#include "Application.h"
#include "Entity.h"
#include "CollisionDatum.h"


class Lochiengine : public Application
{
private:
	std::vector<Entity> entities;
	unsigned int physicsIterations = 30;

	int borderTop = 10;
	int borderBottom = -10;
	int borderLeft = -10;
	int borderRight = 10;

public:

	Lochiengine();

	void Update(float delta) override;
	void OnLeftClick() override;
	void OnRightClick() override;

private:

	void Draw();
	void CollisionHandling();
};

