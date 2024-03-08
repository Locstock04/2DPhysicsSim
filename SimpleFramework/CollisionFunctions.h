#pragma once
#include "Entity.h"

#include "CollisionDatum.h"

CollisionDatum GetCollision(Entity* entityOne, Entity* entityTwo);

CollisionDatum CollideCircleCircle(Entity* entityOne, Entity* entityTwo);
CollisionDatum CollideCircleBox(Entity* entityOne, Entity* entityTwo);
CollisionDatum CollideCirclePlane(Entity* entityOne, Entity* entityTwo);

CollisionDatum CollideBoxBox(Entity* entityOne, Entity* entityTwo);
CollisionDatum CollideBoxPlane(Entity* entityOne, Entity* entityTwo);

CollisionDatum CollidePlanePlane(Entity* entityOne, Entity* entityTwo);
