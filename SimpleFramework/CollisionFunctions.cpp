#include "CollisionFunctions.h"



CollisionDatum GetCollision(Entity* entityOne, Entity* entityTwo)
{
    ShapeType entityOneType = entityOne->shape->GetType();
    ShapeType entityTwoType = entityTwo->shape->GetType();


    switch (entityOneType)
    {
    case ShapeType::Circle:
        switch (entityTwoType)
        {
        case ShapeType::Circle:
            return CollideCircleCircle(entityOne, entityTwo);
        case ShapeType::Box:
            return CollideCircleBox(entityOne, entityTwo);
        case ShapeType::Plane:
            return CollideCirclePlane(entityOne, entityTwo);
        case ShapeType::Line:
            return CollideCircleLine(entityOne, entityTwo);
        default:
            break;
        }
        break;
    case ShapeType::Box:

        break;
    case ShapeType::Plane:
        break;
    case ShapeType::Line:
        break;
    default:
        break;
    }

    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideCircleCircle(Entity* entityOne, Entity* entityTwo)
{
    Circle* entityOneCircle = (Circle*)entityOne->shape;
    Circle* entityTwoCircle = (Circle*)entityTwo->shape;

    CollisionDatum collisionDatum(entityOne, entityTwo);
    Vec2 displacement = entityTwo->pos - entityOne->pos;
    float distance = glm::length(displacement);
    
    collisionDatum.overlap = entityTwoCircle->radius + entityOneCircle->radius - distance;

    

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

CollisionDatum CollideCircleBox(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideCirclePlane(Entity* entityOne, Entity* entityTwo)
{

    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideCircleLine(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideBoxBox(Entity* entityOne, Entity* entityTwo)
{
    CollisionDatum collisionDatum(entityOne, entityTwo);
    return collisionDatum;
}

CollisionDatum CollideBoxPlane(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideBoxLine(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollidePlanePlane(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollidePlaneLine(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}

CollisionDatum CollideLineLine(Entity* entityOne, Entity* entityTwo)
{
    return CollisionDatum(entityOne, entityTwo);
}
