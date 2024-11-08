#include "CollisionFunctions.h"

CollisionDatum GetCollision(Entity* entityOne, Entity* entityTwo)
{
	ShapeType entityOneType = entityOne->shape->getType();
	ShapeType entityTwoType = entityTwo->shape->getType();


	switch (entityOneType)
	{
	case ShapeType::Circle:
		switch (entityTwoType)
		{
		case ShapeType::Circle:
			return CollideCircleCircle(entityOne, entityTwo);
		case ShapeType::Box:
			return CollideCircleBox(entityOne, entityTwo);
		case ShapeType::Plane:
			return CollideCirclePlane(entityOne, entityTwo);
		default:
			break;
		}
	case ShapeType::Box:
		switch (entityTwoType)
		{
		case ShapeType::Circle:
			return CollideCircleBox(entityTwo, entityOne);
		case ShapeType::Box:
			return CollideBoxBox(entityOne, entityTwo);
		case ShapeType::Plane:
			return CollideBoxPlane(entityOne, entityTwo);
		default:
			break;
		}
	case ShapeType::Plane:
		switch (entityTwoType)
		{
		case ShapeType::Circle:
			return CollideCirclePlane(entityTwo, entityOne);
		case ShapeType::Box:
			return CollideBoxPlane(entityTwo, entityOne);
		case ShapeType::Plane:
			return CollidePlanePlane(entityOne, entityTwo);
		default:
			break;
		}
	default:
		break;
	}

	return CollisionDatum(entityOne->physicsObject, entityTwo->physicsObject);
}

CollisionDatum CollideCircleCircle(Entity* entityOne, Entity* entityTwo)
{
	Circle* entityOneCircle = (Circle*)entityOne->shape;
	Circle* entityTwoCircle = (Circle*)entityTwo->shape;

	CollisionDatum collisionDatum(entityOne->physicsObject, entityTwo->physicsObject);
	Vec2 displacement = entityTwo->pos - entityOne->pos;
	float distance = glm::length(displacement);

	collisionDatum.overlap = entityTwoCircle->radius + entityOneCircle->radius - distance;



	// Not colliding
	if (collisionDatum.overlap < 0) {
		return collisionDatum;
	}


	if (distance == 0) {
		// Shapes overlapping completely
		collisionDatum.normal = Vec2(1, 0);
	}
	else {
		// Shapes not overlapping
		collisionDatum.normal = glm::normalize(displacement);
	}

	return collisionDatum;
}

CollisionDatum CollideCircleBox(Entity* entityOne, Entity* entityTwo)
{
	Circle* entityOneCircle = (Circle*)entityOne->shape;
	Box* entityTwoBox = (Box*)entityTwo->shape;

	CollisionDatum collisionDatum(entityOne->physicsObject, entityTwo->physicsObject);

	Vec2 circleClamped(glm::clamp(entityOne->pos, { entityTwoBox->getLeft(), entityTwoBox->getBottom() }, { entityTwoBox->getRight(), entityTwoBox->getTop() }));

	Vec2 displacement = circleClamped - entityOne->pos;
	float centreDistance = glm::length(displacement);


	if (centreDistance <= 0) {

		// Radius does not have to be considered when getting the sides and could instead be added later
		float sides[4] = {
			glm::abs(entityTwoBox->getLeft() - (entityOne->pos.x + entityOneCircle->radius)), // Left
			glm::abs(entityTwoBox->getRight() - (entityOne->pos.x - entityOneCircle->radius)), // Right
			glm::abs(entityTwoBox->getTop() - (entityOne->pos.y - entityOneCircle->radius)), // Up
			glm::abs(entityTwoBox->getBottom() - (entityOne->pos.y + entityOneCircle->radius)) // Down
		};
		int indexOfSmallest = 0;

		for (int i = 1; i < 4; i++)
		{
			if (sides[indexOfSmallest] > sides[i]) {
				indexOfSmallest = i;
			}
		}

		// Funny
		//collisionDatum.normal =  { (indexOfSmallest > 1) ? 0 : ((indexOfSmallest == 0) ? 1 : -1) , (indexOfSmallest < 2) ? 0 : ((indexOfSmallest == 2) ? -1 : 1) }

		switch (indexOfSmallest)
		{
		case 0:
			collisionDatum.normal = { 1, 0 };
			break;
		case 1:
			collisionDatum.normal = { -1, 0 };
			break;
		case 2:
			collisionDatum.normal = { 0, -1 };
			break;
		case 3:
			collisionDatum.normal = { 0, 1 };
			break;
		default:
			break;
		}
		collisionDatum.overlap = sides[indexOfSmallest];
		return collisionDatum;
	}

	collisionDatum.overlap = entityOneCircle->radius - centreDistance;
	collisionDatum.normal = -glm::normalize(entityOne->pos - circleClamped);

	return collisionDatum;
}

CollisionDatum CollideCirclePlane(Entity* entityOne, Entity* entityTwo)
{
	Circle* circleOne = (Circle*)entityOne->shape;
	Plane* planeTwo = (Plane*)entityTwo->shape;

	CollisionDatum collisionDatum(entityOne->physicsObject, entityTwo->physicsObject);
	collisionDatum.normal = -planeTwo->normal;

	float distance = -(glm::dot(entityOne->pos, planeTwo->normal) - planeTwo->displacement);
	collisionDatum.overlap = distance + circleOne->radius;

	return collisionDatum;
}


CollisionDatum CollideBoxBox(Entity* entityOne, Entity* entityTwo)
{
	Box* boxOne = (Box*)entityOne->shape;
	Box* boxTwo = (Box*)entityTwo->shape;

	float oneRightTwoLeft = -boxTwo->getLeft() + boxOne->getRight();
	float oneLeftTwoRight = -boxOne->getLeft() + boxTwo->getRight();
	float oneBottomTwoTop = -boxOne->getBottom() + boxTwo->getTop();
	float oneTopTwoBottom = -boxTwo->getBottom() + boxOne->getTop();

	float sides[4] = { oneRightTwoLeft, oneLeftTwoRight, oneBottomTwoTop, oneTopTwoBottom };
	int indexOfSmallest = 0;
	for (int i = 1; i < 4; i++)
	{
		if (sides[indexOfSmallest] > sides[i]) {
			indexOfSmallest = i;
		}
	}

	CollisionDatum collisionDatum(entityOne->physicsObject, entityTwo->physicsObject);
	collisionDatum.overlap = sides[indexOfSmallest];
	switch (indexOfSmallest)
	{
	case 0:
		collisionDatum.normal = { 1, 0 };
		break;
	case 1:
		collisionDatum.normal = { -1, 0 };
		break;
	case 2:
		collisionDatum.normal = { 0, -1 };
		break;
	case 3:
		collisionDatum.normal = { 0, 1 };
		break;
	default:
		break;
	}
	return collisionDatum;
}

CollisionDatum CollideBoxPlane(Entity* entityOne, Entity* entityTwo)
{
	Box* boxOne = (Box*)entityOne->shape;
	Plane* planeTwo = (Plane*)entityTwo->shape;



	//TODO: Check if leaving early if the distance on any index is greater than the diagonal of the box is worth it
	Vec2 corners[4] = {
		{ boxOne->getLeft(), boxOne->getTop() }, // Top left
		{ boxOne->getRight(), boxOne->getTop() }, // Top right
		{ boxOne->getLeft(), boxOne->getBottom() }, // Bottom left
		{ boxOne->getRight(), boxOne->getBottom() }  // Bottom right
	};
	const int amountOfCorners = 4;

	float distances[amountOfCorners];
	for (int i = 0; i < amountOfCorners; i++)
	{
		distances[i] = -(glm::dot(corners[i], planeTwo->normal) - planeTwo->displacement);
	}
	int indexOfLargest = 0;
	//TODO: Could be a function
	for (int i = 1; i < amountOfCorners; i++)
	{
		if (distances[i] > distances[indexOfLargest]) {
			indexOfLargest = i;
		}
	}

	CollisionDatum collisionDatum(entityOne->physicsObject, entityTwo->physicsObject);

	collisionDatum.overlap = distances[indexOfLargest];
	collisionDatum.normal = -planeTwo->normal;

	return collisionDatum;
}

CollisionDatum CollidePlanePlane(Entity* entityOne, Entity* entityTwo)
{
	return CollisionDatum(entityOne->physicsObject, entityTwo->physicsObject);
}