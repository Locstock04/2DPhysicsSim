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

//TODO: consider having seperate solve based on physics object, is it neccessary/beneficial
void CollisionDatum::Solve()
{
	Vec2 relativeVel = entityTwo->getVel() - entityOne->getVel();

	

	//TODO: what to do with de pen, should it be handled based on/from the physics object itself?
	//TODO: Don't think is working with verlet atm, velocity needs to be kept
	// Depenetration 
	entityOne->setPos(entityOne->getPos() - normal * (overlap * 0.5f));
	entityTwo->setPos(entityTwo->getPos() + normal * (overlap * 0.5f));

	// Already moving apart
	if (glm::dot(normal, relativeVel) >= 0) {
		return;
	}

	//TODO: Elasticity
	float elasticity = 0.8f;
	float combinedInverseMass = entityOne->invMass + entityTwo->invMass;
	//TODO: Is there something specific that should happen here when both inverse mass are zero, should the objects just ignore each other?
	// Currently stopping both of them
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
