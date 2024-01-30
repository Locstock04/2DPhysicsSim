#include "CollisionFunctions.h"



CollisionDatum CircleCircleCheck(Entity& entityOne, Entity& entityTwo)
{
    Vec2 displacement = entityTwo.position - entityTwo.position;
    if (!glm::length(displacement) < entityTwo.radius + entityOne.radius) {
        return;
    }
}
