#include "CollisionDatum.h"

CollisionDatum::CollisionDatum(Entity* one, Entity* two)
{
	entityOne = one;
	entityTwo = two;
}

void CollisionDatum::Solve()
{
	Vec2 vOne = entityOne->getVelocity() * entityOne->VelocityKept;
	Vec2 vTwo = entityTwo->getVelocity() * entityTwo->VelocityKept;

	//entityOne->position -= normal * overlap * 0.5f;
	//entityTwo->position += normal * overlap * 0.5f;

	//entityOne->setVelocity(vOne);
	//entityTwo->setVelocity(vTwo);

	Vec2 j = (2 * glm::dot(vOne - vTwo, normal)) / (normal * (entityOne->invMass + entityTwo->invMass));
	
	entityOne->setVelocity(j);
	entityTwo->setVelocity(-j);


}
