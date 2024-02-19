#pragma once

#include "Application.h"
#include "Entity.h"
#include "CollisionDatum.h"


class Lochiengine : public Application
{
private:
	std::vector<Entity*> entities;
	unsigned int physicsIterations = 20;

	int borderTop = 10;
	int borderBottom = -10;
	int borderLeft = -10;
	int borderRight = 10;


	//float gravitionalConstant = 6.674f * glm::pow(10, 0);
	//float massOfCursor = 5.972 * glm::pow(10, 1);


public:

	Lochiengine();
	~Lochiengine();
	Lochiengine(const Lochiengine& other) = delete;
	Lochiengine& operator=(const Lochiengine& other) = delete;

	void Update(float delta) override;
	void OnLeftClick() override;
	void OnRightClick() override;

private:

	void Draw();
	void CollisionHandling();
};

