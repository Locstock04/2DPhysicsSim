#include "CollisionDatum.h"

CollisionDatum::CollisionDatum(Entity* one, Entity* two)
{
	entityOne = one;
	entityTwo = two;
}

void CollisionDatum::Solve()
{
	Vec2 vOne = entityOne->physicsObject->getVel() * entityOne->VelocityKept;
	Vec2 vTwo = entityTwo->physicsObject->getVel() * entityTwo->VelocityKept;

	Vec2 j = (2 * glm::dot(vOne - vTwo, normal)) / (normal * (entityOne->physicsObject->invMass + entityTwo->physicsObject->invMass));
	
	entityOne->pos -= normal * overlap * 0.5f;
	entityTwo->pos += normal * overlap * 0.5f;

	entityOne->physicsObject->setVel(vOne);
	entityTwo->physicsObject->setVel(vTwo);


	//entityOne->physicsObject->setVel(j);
	//entityTwo->physicsObject->setVel(-j);


}
