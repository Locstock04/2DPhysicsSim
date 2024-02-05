#include "CollisionDatum.h"

CollisionDatum::CollisionDatum(Entity* one, Entity* two)
{
	entityOne = one;
	entityTwo = two;
}

void CollisionDatum::Solve()
{
	Vec2 vOne = entityOne->getVelocity();
	Vec2 vTwo = entityTwo->getVelocity();
	entityOne->position -= normal * overlap * 0.5f;
	entityTwo->position += normal * overlap * 0.5f;

	entityOne->setVelocity(vOne);
	entityTwo->setVelocity(vTwo);

}
