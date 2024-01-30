#pragma once

#include "Application.h"
#include "Entity.h"
#include "CollisionDatum.h"


class Lochiengine : public Application
{
private:
	std::vector<Entity> entities;

public:

	Lochiengine();

	void Update(float delta) override;
	void OnLeftClick() override;

private:

	void Draw();
	std::vector<CollisionDatum> CollisionDetection();
	void CollisionResponse();
};

