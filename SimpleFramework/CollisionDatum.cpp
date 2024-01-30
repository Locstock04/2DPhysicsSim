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

	if (entityOne->position.y < -10 + entityOne->radius) {
		entityOne->position.y = -10 + entityOne->radius;
	}
	if (entityOne->position.y > 10 - entityOne->radius) {
		entityOne->position.y = 10 - entityOne->radius;
	}
	if (entityOne->position.x < -10 + entityOne->radius) {
		entityOne->position.x = -10 + entityOne->radius;
	}
	if (entityOne->position.x > 10 - entityOne->radius) {
		entityOne->position.x = 10 - entityOne->radius;
	}

	if (entityTwo->position.y < -10 + entityTwo->radius) {
		entityTwo->position.y = -10 + entityTwo->radius;
	}
	if (entityTwo->position.y > 10 - entityTwo->radius) {
		entityTwo->position.y = 10 - entityTwo->radius;
	}
	if (entityTwo->position.x < -10 + entityTwo->radius) {
		entityTwo->position.x = -10 + entityTwo->radius;
	}
	if (entityTwo->position.x > 10 - entityTwo->radius) {
		entityTwo->position.x = 10 - entityTwo->radius;
	}

}
