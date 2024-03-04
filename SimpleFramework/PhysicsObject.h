#pragma once

#include "Maths.h"

class Entity;


enum class PhysicsObjectType {
	Euler,
	Verlet,
	Static,
};


class PhysicsObject {
public:
	Entity* parent;
	float invMass = 1;

	PhysicsObject() = default;
	PhysicsObject(Entity* _parent);

	virtual Vec2 getVel() const = 0;
	virtual Vec2 getAcc() const = 0;
	virtual Vec2 getPos() const = 0;
	virtual void setPos(Vec2 _pos) = 0;
	virtual void setVel(Vec2 _vel) = 0;
	virtual void setAcc(Vec2 _acc) = 0;

	void setMass(float mass);
	float getMass();

	virtual void AddImpulse(Vec2 dir);

	virtual void Update(float delta) = 0;

	virtual bool isStatic() const { return false; };
	virtual PhysicsObjectType getType() const = 0;

	static Vec2 gravity;


protected:

};

class VerletObject : public PhysicsObject {

	Vec2 oldPos;
	Vec2 acc;

public:

	VerletObject() = default;
	VerletObject(Entity* _parent);
	void Update(float delta) override;

	void setVel(Vec2 _vel) override;
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override;
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override;
	Vec2 getPos() const override;

	virtual PhysicsObjectType getType() const override { return PhysicsObjectType::Verlet; };


};

class EulerObject : public PhysicsObject {

	Vec2 vel;
	Vec2 acc;

public:

	EulerObject() = default;
	EulerObject(Entity* _parent);
	void Update(float delta) override;

	void setVel(Vec2 _vel) override;
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override;
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override;
	Vec2 getPos() const override;

	virtual PhysicsObjectType getType() const override { return PhysicsObjectType::Euler; };
};

class StaticObject : public PhysicsObject {

public:

	StaticObject() = default;
	StaticObject(Entity* _parent);
	void Update(float delta) override {};

	void setVel(Vec2 _vel) override {};
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override {};
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override {};
	Vec2 getPos() const override;

	virtual bool isStatic() const { return true; };
	virtual PhysicsObjectType getType() const override { return PhysicsObjectType::Static; };
};