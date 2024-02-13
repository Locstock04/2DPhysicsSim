#include "CollisionFunctions.h"



CollisionDatum GetCollision(Entity* entityOne, Entity* entityTwo)
{
    ShapeType entityOneType = entityOne->shape->getType();
    ShapeType entityTwoType = entityTwo->shape->getType();


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
    case ShapeType::Box:
        switch (entityTwoType)
        {
        case ShapeType::Circle:
            return CollideCircleBox(entityTwo, entityOne);
        case ShapeType::Box:
            return CollideBoxBox(entityOne, entityTwo);
        case ShapeType::Plane:
            return CollideBoxPlane(entityOne, entityTwo);
        case ShapeType::Line:
            return CollideBoxLine(entityOne, entityTwo);
        default:
            break;
        }
    case ShapeType::Plane:
        switch (entityTwoType)
        {
        case ShapeType::Circle:
            return CollideCirclePlane(entityTwo, entityOne);
        case ShapeType::Box:
            return CollideBoxPlane(entityTwo, entityOne);
        case ShapeType::Plane:
            return CollidePlanePlane(entityOne, entityTwo);
        case ShapeType::Line:
            return CollidePlaneLine(entityOne, entityTwo);
        default:
            break;
        }

    case ShapeType::Line:
        switch (entityTwoType)
        {
        case ShapeType::Circle:
            return CollideCircleLine(entityTwo, entityOne);
        case ShapeType::Box:
            return CollideBoxLine(entityTwo, entityOne);
        case ShapeType::Plane:
            return CollidePlaneLine(entityTwo, entityOne);
        case ShapeType::Line:
            return CollideLineLine(entityOne, entityTwo);
        default:
            break;
        }
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
    Circle* entityOneCircle = (Circle*)entityOne->shape;
    Box* entityTwoBox = (Box*)entityTwo->shape;

    CollisionDatum collisionDatum(entityOne, entityTwo);
    //Vec2 displacement = entityTwo->pos - entityOne->pos;
    //float distance = glm::length(displacement);




    return collisionDatum;
}

CollisionDatum CollideCirclePlane(Entity* entityOne, Entity* entityTwo)
{
    Circle* entityOneCircle = (Circle*)entityOne->shape;
    Plane* entityTwoPlane = (Plane*)entityTwo->shape;

    CollisionDatum collisionDatum(entityOne, entityTwo);
    collisionDatum.normal = {entityTwoPlane->normal}

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
