#include "PhysicsObject.h"

#include "Entity.h"

Vec2 PhysicsObject::gravity = Vec2(0, -3);


PhysicsObject::PhysicsObject(Entity* _parent)
{
	invMass = 1;
	parent = _parent;

}

void PhysicsObject::setPos(Vec2 _pos) {
	parent->pos = _pos;
}

void PhysicsObject::setMass(float mass)
{
	// inverseMass = 1 /
}

void PhysicsObject::AddImpulse(Vec2 dir)
{
	setVel(getVel() + (dir * invMass));
}

void VerletObject::Update(float delta)
{
	Vec2 oldPosTemp = parent->pos;
	parent->pos = (2.f * parent->pos) - oldPos + (acc + gravity) * (delta * delta);
	oldPos = oldPosTemp;
}

VerletObject::VerletObject(Entity* _parent) : PhysicsObject(_parent)
{
	acc = { 0, 0 };
	oldPos = _parent->pos;
}


EulerObject::EulerObject(Entity* _parent) : PhysicsObject(_parent) {
	vel = { 0, 0 };
	acc = { 0, 0 };
}

void EulerObject::Update(float delta)
{
	//TODO: Acc
	vel += (gravity + acc) * delta;
	parent->pos += vel * delta;
}

void VerletObject::setVel(Vec2 v)
{
	// v = pos - oldPos
	// v + oldPos = pos
	// oldPos = pos - v

	oldPos = parent->pos - v;
}

Vec2 VerletObject::getVel() const
{
	return parent->pos - oldPos;
}

void VerletObject::setAcc(Vec2 _acc)
{
	acc = _acc;
}

Vec2 VerletObject::getAcc() const
{
	return acc;
}

void VerletObject::setPos(Vec2 _pos)
{
	//TODO:
	parent->pos = _pos;
}

Vec2 VerletObject::getPos() const
{
	return parent->pos;
}


void EulerObject::setVel(Vec2 v)
{
	vel = v;
}

Vec2 EulerObject::getVel() const
{
	return vel;
}

void EulerObject::setAcc(Vec2 _acc)
{
	acc = _acc;
}

Vec2 EulerObject::getAcc() const
{
	return acc;
}

void EulerObject::setPos(Vec2 _pos)
{
	parent->pos = _pos;
}

Vec2 EulerObject::getPos() const
{
	return parent->pos;
}

StaticObject::StaticObject(Entity* _parent) : PhysicsObject(_parent)
{
	invMass = 0;
	isStatic = true;
}

Vec2 StaticObject::getVel() const
{
	return { 0.f, 0.f };
}

Vec2 StaticObject::getAcc() const
{
	return { 0.f, 0.f };
}

Vec2 StaticObject::getPos() const
{
	return parent->pos;
}
