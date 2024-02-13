#include "CollisionDatum.h"

CollisionDatum::CollisionDatum(Entity* one, Entity* two)
{
	entityOne = one;
	entityTwo = two;
}

void CollisionDatum::Solve()
{
	Vec2 relativeVel = entityTwo->physicsObject->getVel() - entityOne->physicsObject->getVel();

	// Already moving apart
	if (glm::dot(normal, relativeVel) >= 0) {
		return;
	}

	float elasticity = 1.f;
	float combinedInverseMass = entityOne->physicsObject->invMass + entityTwo->physicsObject->invMass;
	Vec2 j = (glm::dot(-(1 + elasticity) * (relativeVel), normal) / (combinedInverseMass)) * normal;
	

	//entityOne->pos -= normal * overlap * 0.5f;
	//entityTwo->pos += normal * overlap * 0.5f;

	//entityOne->physicsObject->setVel(vOne);
	//entityTwo->physicsObject->setVel(vTwo);

	//TODO: Change to impulse
	entityOne->physicsObject->setVel(-j);
	entityTwo->physicsObject->setVel(j);


}
