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
	float invMass;


	//TODO: Would a function be better
	bool isStatic = false;

	PhysicsObject(Entity* _parent);

	virtual Vec2 getVel() const = 0;
	virtual Vec2 getAcc() const = 0;
	virtual Vec2 getPos() const = 0;
	virtual void setPos(Vec2 _pos) = 0;
	virtual void setVel(Vec2 _vel) = 0;
	virtual void setAcc(Vec2 _acc) = 0;

	void setMass(float mass);

	virtual void AddImpulse(Vec2 dir);

	virtual void Update(float delta) = 0;

	//bool isStatic() const { return isStatic; };

	static Vec2 gravity;


protected:

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
	Vec2 getPos() const override;

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
	Vec2 getPos() const override;
};

class StaticObject : public PhysicsObject {

public:

	StaticObject(Entity* _parent);
	void Update(float delta) override {};

	void setVel(Vec2 _vel) override {};
	Vec2 getVel() const override;
	void setAcc(Vec2 _acc) override {};
	Vec2 getAcc() const override;
	void setPos(Vec2 _pos) override {};
	Vec2 getPos() const override;

	//virtual bool isStatic() const { return true; };
};