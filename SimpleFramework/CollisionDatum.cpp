#include "CollisionDatum.h"

CollisionDatum::CollisionDatum(Entity* one, Entity* two)
{
	entityOne = one;
	entityTwo = two;
}

void CollisionDatum::Solve()
{
	entityOne->position -= normal * overlap * 0.5f;
	entityTwo->position += normal * overlap * 0.5f;

	

}
