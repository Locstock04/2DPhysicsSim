#include "CollisionDatum.h"



CollisionDatum::CollisionDatum(Entity* one, Entity* two) :
	entityOne(one),
	entityTwo(two)
{
}

CollisionDatum::CollisionDatum()
{
}
CollisionDatum* CollisionDatum::emptyTemp = new CollisionDatum;

void CollisionDatum::Solve()
{
	Vec2 relativeVel = entityTwo->physicsObject->getVel() - entityOne->physicsObject->getVel();

	// Already moving apart
	if (glm::dot(normal, relativeVel) >= 0) {
		return;
	}
	//TODO: move objects apart if relative vel is zero
	//else if ()

	//TODO: Elasticity
	float elasticity = 0.9f;
	float combinedInverseMass = entityOne->physicsObject->invMass + entityTwo->physicsObject->invMass;
	//if (combinedInverseMass = )
	Vec2 j = (glm::dot(-(1 + elasticity) * (relativeVel), normal) / (combinedInverseMass)) * normal;
	

	//entityOne->pos -= normal * overlap * 0.5f;
	//entityTwo->pos += normal * overlap * 0.5f;n

	entityOne->physicsObject->AddImpulse(-j);
	entityTwo->physicsObject->AddImpulse(j);


}
