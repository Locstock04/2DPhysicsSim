#include "CollisionFunctions.h"



CollisionDatum CircleCircleCheck(Entity* entityOne, Entity* entityTwo)
{
    CollisionDatum collisionDatum(entityOne, entityTwo);
    Vec2 displacement = entityTwo->position - entityOne->position;
    float distance = glm::length(displacement);
    
    collisionDatum.overlap = entityTwo->radius + entityOne->radius - distance;

    

    // Not colliding
    if (collisionDatum.overlap < 0) {
        return collisionDatum;
    }


    
    if (distance == 0) {
        // Shapes overlapping completely
        collisionDatum.normal = Vec2(1, 0);
    }
    else {
        // Shapes not overlapping
        collisionDatum.normal = glm::normalize(displacement);
    }

    return collisionDatum;
}

CollisionDatum BoxBoxCheck(Entity* entityOne, Entity* entityTwo)
{
    CollisionDatum collisionDatum(entityOne, entityTwo);
    return collisionDatum;
}
