#include "CollisionDatum.h"



CollisionDatum::CollisionDatum(PhysicsObject* one, PhysicsObject* two) :
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
	Vec2 relativeVel = entityTwo->getVel() - entityOne->getVel();

	// Already moving apart
	if (glm::dot(normal, relativeVel) >= 0) {
		return;
	}
	//TODO: move objects apart if relative vel is zero
	//else if ()

	//TODO: Elasticity
	float elasticity = 0.9f;
	float combinedInverseMass = entityOne->invMass + entityTwo->invMass;
	//TODO: Is there something specific that should happen here
	if (combinedInverseMass == 0) {
		entityOne->setVel({ 0.f, 0.f });
		entityOne->setAcc({ 0.f, 0.f });
		entityTwo->setVel({ 0.f, 0.f });
		entityTwo->setAcc({ 0.f, 0.f });
		return;
	}
	//if (combinedInverseMass = )
	Vec2 j = (glm::dot(-(1 + elasticity) * (relativeVel), normal) / (combinedInverseMass)) * normal;
	

	//entityOne->pos -= normal * overlap * 0.5f;
	//entityTwo->pos += normal * overlap * 0.5f;n

	entityOne->AddImpulse(-j);
	entityTwo->AddImpulse(j);


}
