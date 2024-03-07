#pragma once

#include "Application.h"
#include "Entity.h"
#include "CollisionDatum.h"
#include "GUI.h"


class Lochiengine : public Application
{
private:
	std::vector<Entity*> entities;
	unsigned int collisionIterations = 20;


	//float gravitionalConstant = 6.674f * glm::pow(10, 0);
	//float massOfCursor = 5.972 * glm::pow(10, 1);

	// Allow the GUI to access private variables
	friend class GUI;
	GUI gui;



public:

	Lochiengine();
	~Lochiengine();
	Lochiengine(const Lochiengine& other) = delete;
	Lochiengine& operator=(const Lochiengine& other) = delete;

	// The delta value given to update should remain consistent and be unchanging. Variable time-rate has not been tested
	void Update(float delta) override;
	void OnLeftClick() override;
	void OnRightClick() override;

private:

	void Draw();
	void CollisionHandling();
};

