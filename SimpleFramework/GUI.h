#pragma once
#include "Entity.h"

class Lochiengine;

class GUI
{
public:

	Entity* creatingEntity;
private:
	// GUI Stuff
	// Entity GUI
	bool drawCreatingShape = true;

	float colour[3] = { 1.f, 1.f, 1.f };
	float entityPos[2] = { 0.f, 0.f };

	float mass;
	bool infiniteMass;
	// A seperate pos, this one goes through the physics object while the other pos is referenced and applied directly to the entity
	float pos[2] = { 0, 0 };
	float vel[2] = { 0, 0 };
	float acc[2] = { 0, 0 };


	bool editMode = false;
	int editIndex = 0;
	// Force

	bool applyToAll = true;
	int forceIndex = 0;

	float toApply[2];
	float gravity[2];

	

public:
	Lochiengine* lochiengine;

	GUI();
	~GUI();
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI& other) = delete;

	void Update(LineRenderer* lines);

private:

	void ForceMenu();
	void EntityEditorMenu();
	void PresetMenu();
	void EntityGUI(Entity* entity);
	void ShapeGUI(Entity* entity);
	void PhysicsObjectGUI(Entity* entity);

};

