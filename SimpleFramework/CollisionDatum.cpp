#include "CollisionDatum.h"

float CollisionDatum::elasticity = 0.8f;


CollisionDatum::CollisionDatum(PhysicsObject* one, PhysicsObject* two) :
	objectOne(one),
	objectTwo(two)
{
}

void CollisionDatum::Solve()
{
	Vec2 relativeVel = objectTwo->getVel() - objectOne->getVel();

	
	//TODO: Change how depenetration is calculated depending on the mass of the objects
	//TODO: what to do with de pen, should it be handled based on/from the physics object itself? The physics object could have a function itself. Verlet could depen by the neccessary amount to get the required 'velocity'
	// Depenetration 

	objectOne->AddDepenetration(-normal * (overlap * 0.5f));
	objectTwo->AddDepenetration(normal * (overlap * 0.5f));

	//objectOne->setPos(objectOne->getPos() - normal * (overlap * 0.5f));
	//objectTwo->setPos(objectTwo->getPos() + normal * (overlap * 0.5f));

	// Already moving apart 
	if (glm::dot(normal, relativeVel) >= 0) {
		return;
	}

	//TODO: Elasticity

	float combinedInverseMass = objectOne->invMass + objectTwo->invMass;
	//TODO: Is there something specific that should happen here when both inverse mass are zero, should the objects just ignore each other, stop each other, or act as if they have the same mass
	if (combinedInverseMass == 0) {
		return;
	}
	Vec2 j = (-(1 + elasticity) * glm::dot(relativeVel, normal) / (combinedInverseMass)) * normal;
	
	objectOne->AddImpulse(-j);
	objectTwo->AddImpulse(j);
}
