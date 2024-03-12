#pragma once
#include "Entity.h"

class Lochiengine;

class GUI
{
public:
	Lochiengine* lochiengine = nullptr;

	Entity* creatingEntity;
private:
	// GUI Stuff
	// Entity GUI
	bool drawCreatingShape = true;

	float entityPos[2] = { 0.f, 0.f };

	bool infiniteMass = false;


	bool editMode = false;
	int editIndex = 0;
	// Force

	bool applyToAll = true;
	int forceIndex = 0;

	float toApply[2] = { 0, 0 };

public:

	GUI();
	~GUI();
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI& other) = delete;

	void Update();

private:

	void InfoMenu();
	void InteractionMenu();
	void EntityEditorMenu();
	void PresetMenu();
	void EntityGUI(Entity* entity);
	void ShapeGUI(Entity* entity);
	void PhysicsObjectGUI(Entity* entity);

};

