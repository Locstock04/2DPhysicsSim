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

	static Vec2 gravity;
	// Is needed to ensure values are in the correct unit ( units / second ).
	static float updatesPerSecond;
	// Changes how depenetration is applied and calculated
	static bool ApplyDepenetrationInstantly;


	virtual Vec2 getVel() const = 0;
	virtual Vec2 getAcc() const = 0;
	virtual Vec2 getPos() const = 0;
	virtual void setPos(Vec2 _pos) = 0;
	virtual void setVel(Vec2 _vel) = 0;
	virtual void setAcc(Vec2 _acc) = 0;
	virtual void Update(float delta) = 0;
	virtual PhysicsObjectType getType() const = 0;

	void setMass(float mass);
	float getMass() const;

	//TODO: what to do with de pen, should it be handled based on/from the physics object itself? The physics object subclasses could have a function itself. Verlet could depen by the neccessary amount to get the required 'velocity'? which would require changes to collisionDatums solve function.
	virtual void AddDepenetration(Vec2 depenetration);

	virtual void AddImpulse(Vec2 dir);
	virtual void AddForce(Vec2 force);
	virtual void AddVelocity(Vec2 velocity);
	//TODO: an Add Acceleration function

protected:
	Vec2 forceAccumulator = { 0, 0 };
	Vec2 netDepenetration = { 0, 0 };
	//TODO: Ensure that this is this alright to do, having the constructors be protected (if so other classes can be changed to match)
	PhysicsObject() = default;
	PhysicsObject(Entity* _parent);


	void ApplyDepenetration();

};

class VerletObject : public PhysicsObject {
private:
	Vec2 oldPos;
	Vec2 acc;

public:

	VerletObject();
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
private:
	Vec2 vel = { 0, 0 };
	Vec2 acc = { 0, 0 };

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

	void AddDepenetration(Vec2 depenetration) override;

	virtual PhysicsObjectType getType() const override { return PhysicsObjectType::Static; };
};