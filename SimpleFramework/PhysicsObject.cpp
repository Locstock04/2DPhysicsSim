#include "PhysicsObject.h"

#include "Entity.h"

Vec2 PhysicsObject::gravity = Vec2(0, 0);

float PhysicsObject::updatesPerSecond = 0.f;

bool PhysicsObject::ApplyDepenetrationInstantly = true;

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
	// inverseMass = 1 / mass
	//TODO: Should there be a zero check here
	invMass = 1 / mass;
}

float PhysicsObject::getMass() const
{
	return 1 / invMass;
}

void PhysicsObject::AddDepenetration(Vec2 depenetration)
{
	if (ApplyDepenetrationInstantly) {
		setPos(getPos() + depenetration);
		return;
	}
	// else
	if (abs(depenetration.x) + abs(depenetration.y) <= 0.000001f) return;
	if (glm::dot(depenetration, netDepenetration) <= 0.000001f) {
		netDepenetration += depenetration;
		return;
	}
	// else

	Vec2 netNormal = glm::normalize(netDepenetration);
	float amountAlreadyDepened = glm::dot(netNormal, depenetration);
	Vec2 changeInNet = netDepenetration - amountAlreadyDepened * netNormal;
	if (glm::dot(changeInNet, netDepenetration) < 0.f)
	{
		netDepenetration = depenetration;
	}
	else {
		netDepenetration = changeInNet + depenetration;
	}
}

void PhysicsObject::ApplyDepenetration()
{
	if (abs(netDepenetration.x) < 0.00001 && abs(netDepenetration.y) < 0.00001) {
		return;
	}
	setPos(getPos() + netDepenetration);
	netDepenetration = { 0, 0 };
}

void PhysicsObject::AddImpulse(Vec2 dir)
{
	setVel(getVel() + (dir * invMass));
}

void PhysicsObject::AddForce(Vec2 force)
{
	forceAccumulator += force;
}

void PhysicsObject::AddVelocity(Vec2 velocity)
{
	setVel(getVel() + velocity);
}

void VerletObject::Update(float delta)
{
	Vec2 oldPosTemp = parent->pos;
	parent->pos += parent->pos - oldPos + (forceAccumulator * invMass) + (acc + gravity) * (delta * delta);
	oldPos = oldPosTemp;

	/*Vec2 newPos = parent->pos + (parent->pos - oldPos) + (acc + gravity) * (delta * delta);
	oldPos = parent->pos;
	parent->pos = newPos;*/

	ApplyDepenetration();
}

VerletObject::VerletObject() :
	acc({ 0, 0 }),
	oldPos({ 0, 0 })
{
}

VerletObject::VerletObject(Entity* _parent) : PhysicsObject(_parent),
acc({ 0, 0 }),
oldPos(_parent->pos)
{
}


EulerObject::EulerObject(Entity* _parent) : PhysicsObject(_parent) {
}

void EulerObject::Update(float delta)
{
	vel += (gravity + acc + (forceAccumulator * invMass)) * delta;
	parent->pos += vel * delta;

	ApplyDepenetration();
}

void VerletObject::setVel(Vec2 v)
{
	// velocity = position - oldPosition
	// velocity + oldPosition = position
	// oldPosition = position - velocity

	// Divide by updates per second to have the velocity set in the correct unit (over second instead of frame)
	v /= updatesPerSecond;
	oldPos = parent->pos - v;
}

Vec2 VerletObject::getVel() const
{
	// Multiply by updates per second to have the velocity return in the correct unit (over second instead of frame)
	return (parent->pos - oldPos) * updatesPerSecond;
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
	//TODO: Should this teleport or zoom the object to this position, currently teleporting. When the pos is moved via the entity.pos itself, it zooms
	Vec2 oldVel = getVel();
	parent->pos = _pos;
	setVel(oldVel);
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

void StaticObject::AddDepenetration(Vec2 depenetration)
{
}
