#pragma once

#include "Maths.h"

class Entity;

class PhysicsObject {
public:
	Entity* parent;
	float invMass;

	PhysicsObject(Entity* _parent);

	virtual Vec2 getVel() const = 0;
	virtual Vec2 getAcc() const = 0;
	virtual void setPos(Vec2 _pos) = 0;
	virtual void setVel(Vec2 _vel) = 0;
	virtual void setAcc(Vec2 _acc) = 0;

	virtual void AddImpulse(Vec2 dir);

	virtual void Update(float delta) = 0;
protected:



	Vec2 gravity;

};

class VerletObject : public PhysicsObject {

	Vec2 oldPos;
	Vec2 acc;

public:

	VerletObject(Entity* _parent);
	void Update(float delta) override;

	void setVel(Vec2 _vel) override;
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override;
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override;

};

class EulerObject : public PhysicsObject {

	Vec2 vel;
	Vec2 acc;

public:

	EulerObject(Entity* _parent);
	void Update(float delta) override;

	void setVel(Vec2 _vel) override;
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override;
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override;


};