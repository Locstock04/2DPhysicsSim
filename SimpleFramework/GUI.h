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
	float shapePos[2] = { 0.f, 0.f };

	float mass;
	bool infiniteMass;

	bool editMode = false;
	int selectionIndex = 0;
	// Force

	bool applyToAll = true;

	

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
	void EntityGUI(Entity* entity);

};

