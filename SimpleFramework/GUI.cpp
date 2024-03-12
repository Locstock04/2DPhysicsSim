#include "GUI.h"

#include "Lochiengine.h"

#include "Maths.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


GUI::GUI()
{
	creatingEntity = new Entity({ 0.f, 0.f }, new Circle(1), new EulerObject());
}

GUI::~GUI()
{
	delete creatingEntity;
}

void GUI::Update()
{
	if (!editMode && drawCreatingShape && creatingEntity->shape != nullptr) {
		creatingEntity->Draw();
	}

	EntityEditorMenu();
	InteractionMenu();
	PresetMenu();
	InfoMenu();
}

void GUI::InfoMenu()
{
	if (!ImGui::Begin("Information", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Left click to place a default entity, (Circle, Euler)");
	ImGui::Text("Right click to add force to all entities toward the mouse cursor");

	ImGui::End();
}

void GUI::InteractionMenu()
{
	if (!ImGui::Begin("Interactions and Forces", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}

	float newGravity[2] = { PhysicsObject::gravity.x, PhysicsObject::gravity.y };
	if (ImGui::DragFloat2("Gravity", newGravity, 0.1f, -FLT_MAX, FLT_MAX)) {
		PhysicsObject::gravity = { newGravity[0], newGravity[1] };
	}
	ImGui::DragFloat("Cursor Pull Force", &lochiengine->pullForce, 0.1f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat("Elasticity", &CollisionDatum::elasticity, 0.001f, 0.f, 1.f);
	ImGui::Checkbox("Apply Depentration Instantly Mode", &PhysicsObject::ApplyDepenetrationInstantly);
	ImGui::Checkbox("Apply To All Entities", &applyToAll);

	if (!applyToAll) {
		ImGui::SliderInt("Index", &forceIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		forceIndex = glm::clamp(forceIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		//TODO: Show some sort of text for when there are no entities to edit
	}

	ImGui::DragFloat2("Vec2", toApply, 0.1f, -FLT_MAX, FLT_MAX);

	// TODO: These buttons could be cleaned up by having some sort of force mode with a new function
	if (ImGui::Button("Add as impulse")) {
		Vec2 impulse = { toApply[0], toApply[1] };
		if (applyToAll) {
			for (int i = 0; i < lochiengine->entities.size(); i++)
			{
				lochiengine->entities[i]->physicsObject->AddImpulse(impulse);
			}
		}
		else {
			if (lochiengine->entities.size() != 0) {
				lochiengine->entities[forceIndex]->physicsObject->AddImpulse(impulse);
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Add force")) {
		Vec2 force = { toApply[0], toApply[1] };
		if (applyToAll) {
			for (int i = 0; i < lochiengine->entities.size(); i++)
			{
				lochiengine->entities[i]->physicsObject->AddForce(force);
			}
		}
		else {
			if (lochiengine->entities.size() != 0) {
				lochiengine->entities[forceIndex]->physicsObject->AddForce(force);
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Set Velocity")) {
		Vec2 velocity = { toApply[0], toApply[1] };
		if (applyToAll) {
			for (int i = 0; i < lochiengine->entities.size(); i++)
			{
				lochiengine->entities[i]->physicsObject->setVel(velocity);
			}
		}
		else {
			if (lochiengine->entities.size() != 0) {
				lochiengine->entities[forceIndex]->physicsObject->setVel(velocity);
			}
		}
	}
	ImGui::End();
}

void GUI::EntityEditorMenu()
{
	if (!ImGui::Begin("Entity Menu", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}

	ImGui::Checkbox("Edit Existing Object", &editMode);
	if (editMode) {
		ImGui::SliderInt("Index", &editIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		editIndex = glm::clamp(editIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		//TODO: Show some sort of text for when there are no entities to edit
		if (lochiengine->entities.size() != 0) {
			EntityGUI(lochiengine->entities[editIndex]);
		}
		ImGui::End();
		return;
	}
	ImGui::Checkbox("Preview Entity", &drawCreatingShape);
	EntityGUI(creatingEntity);

	ImGui::Spacing();
	//TODO: Add the ability to create an entity duplicated of the currently selected entity
	if (ImGui::Button("Create object")) {
		Shape* newShape;
		//TODO: I feel like this switch could be better written
		switch (creatingEntity->shape->getType())
		{
		case ShapeType::Circle:
			//TODO: Find out if there is another way to write the below line
			newShape = new Circle(*(Circle*)creatingEntity->shape);
			break;
		case ShapeType::Box:
			newShape = new Box(*(Box*)creatingEntity->shape);
			break;
		case ShapeType::Plane:
			newShape = new Plane(*(Plane*)creatingEntity->shape);
			break;
		default:
			//TODO: What here
			newShape = new Circle(*(Circle*)creatingEntity->shape);
			break;
		}

		PhysicsObject* newPhysicsObject;
		switch (creatingEntity->physicsObject->getType())
		{
		case PhysicsObjectType::Euler:
			newPhysicsObject = new EulerObject(*(EulerObject*)creatingEntity->physicsObject);
			break;
		case PhysicsObjectType::Verlet:
			newPhysicsObject = new VerletObject(*(VerletObject*)creatingEntity->physicsObject);
			break;
		case PhysicsObjectType::Static:
			newPhysicsObject = new StaticObject(*(StaticObject*)creatingEntity->physicsObject);
			break;
		default:
			newPhysicsObject = new EulerObject(*(EulerObject*)creatingEntity->physicsObject);

			break;
		}
		lochiengine->entities.push_back(new Entity({ entityPos[0], entityPos[1] }, newShape, newPhysicsObject));

	}
	ImGui::End();

}

// TODO: The presets could be more customisable
void GUI::PresetMenu()
{
	if (!ImGui::Begin("Preset Menu", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}
	if (ImGui::Button("Destroy All Entities")) {
		while (!lochiengine->entities.empty())
		{
			delete lochiengine->entities.back();
			lochiengine->entities.pop_back();
		}
	}
	// TODO: Make the n sides plane a function
	else if (ImGui::Button("Circle made of planes")) {
		int lineSides = 90;
		for (int i = 0; i < lineSides; i++)
		{
			lochiengine->entities.push_back(new Entity({ 0, 0 }, new Plane(float(i * (360 / lineSides)), -10)));
		}
	}
	else if (ImGui::Button("Box made from planes")) {
		int lineSides = 4;
		for (int i = 0; i < lineSides; i++)
		{
			lochiengine->entities.push_back(new Entity({ 0, 0 }, new Plane(float(i * (360 / lineSides)), -10)));
		}
	}
	else if (ImGui::Button("10 circles")) {
		for (int i = 0; i < 10; i++)
		{
			lochiengine->entities.push_back(new Entity({ 0, 0 }, new Circle(1), new EulerObject()));
		}
	}

	ImGui::End();
}

void GUI::EntityGUI(Entity* entity)
{
	if (ImGui::CollapsingHeader("Entity")) {
		entityPos[0] = entity->pos.x;
		entityPos[1] = entity->pos.y;
		if (ImGui::DragFloat2("Position##Entity", entityPos, 0.1f, 1.f)) {
			entity->pos = { entityPos[0], entityPos[1] };
		}
	}

	if (ImGui::CollapsingHeader("Shape")) {
		ShapeGUI(entity);
	}

	if (ImGui::CollapsingHeader("Physics")) {
		PhysicsObjectGUI(entity);
	}
}

void GUI::ShapeGUI(Entity* entity)
{
	Shape*& shape = entity->shape;


	std::string shapeName;
	switch (shape->getType())
	{
	case ShapeType::Circle:
		shapeName = "Circle";
		break;
	case ShapeType::Box:
		shapeName = "Box";
		break;
	case ShapeType::Plane:
		shapeName = "Plane";
		delete entity->physicsObject;
		entity->physicsObject = new StaticObject(entity);
		break;
	default:
		break;
	}

	ImGui::Text("Shape");
	ImGui::SameLine();
	if (ImGui::Button(shapeName.c_str())) {
		ImGui::OpenPopup("Shape Type");
	}
	//TODO: Switching shapes doesn't refresh colour
	if (ImGui::IsPopupOpen("Shape Type")) {
		ImGui::BeginPopup("Shape Type");
		if (ImGui::Button("Circle")) {
			delete shape;
			shape = new Circle(entity, 1);
			ImGui::CloseCurrentPopup();
		}
		else if (ImGui::Button("Box")) {
			delete shape;
			shape = new Box(entity, 1, 1);
			ImGui::CloseCurrentPopup();
		}
		else if (ImGui::Button("Plane")) {
			delete shape;
			shape = new Plane(entity, { 1.f, 0.f }, -1.f);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	float tempWidth;
	float tempHeight;
	float tempAngle;
	float tempColour[3] = { shape->colour.x, shape->colour.y, shape->colour.z };
	if (ImGui::ColorEdit3("Colour", tempColour)) {
		shape->colour = { tempColour[0], tempColour[1], tempColour[2] };
	}
	switch (entity->shape->getType())
	{
	case ShapeType::Circle:
		ImGui::DragFloat("Radius", &((Circle*)(shape))->radius, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
		break;
	case ShapeType::Box:
		tempWidth = ((Box*)(shape))->getWidth();
		tempHeight = ((Box*)(shape))->getHeight();
		if (ImGui::DragFloat("Width", &tempWidth, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			((Box*)(shape))->setWidth(tempWidth);
		}
		if (ImGui::DragFloat("Height", &tempHeight, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			((Box*)(shape))->setHeight(tempHeight);
		}
		break;
	case ShapeType::Plane:
		tempAngle = ((Plane*)(shape))->getNormalDegrees();
		ImGui::DragFloat("Displacement", &((Plane*)(shape))->displacement, 0.1f, -FLT_MAX, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
		if (ImGui::DragFloat("Angle", &tempAngle, 0.1f, -FLT_MAX, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			((Plane*)(shape))->setNormal(tempAngle);
		}


		break;
	default:
		//TODO: what here
		break;
	}
}

void GUI::PhysicsObjectGUI(Entity* entity)
{
	PhysicsObject*& physicsObject = entity->physicsObject;

	float pos[2] = { physicsObject->getPos().x, physicsObject->getPos().y };
	float vel[2] = { physicsObject->getVel().x, physicsObject->getVel().y };
	float acc[2] = { physicsObject->getAcc().x, physicsObject->getAcc().y };

	std::string physicsTypeName;
	switch (physicsObject->getType())
	{
	case PhysicsObjectType::Euler:
		physicsTypeName = "Euler";
		break;
	case PhysicsObjectType::Verlet:
		physicsTypeName = "Verlet";
		break;
	case PhysicsObjectType::Static:
		physicsTypeName = "Static";
		break;
	default:
		break;
	}

	ImGui::Text("Physics Type");
	ImGui::SameLine();
	if (ImGui::Button(physicsTypeName.c_str())) {
		ImGui::OpenPopup("Physics Type");
	}

	if (ImGui::IsPopupOpen("Physics Type")) {
		ImGui::BeginPopup("Physics Type");
		bool switched = false;
		if (ImGui::Button("Euler")) {
			delete physicsObject;
			physicsObject = new EulerObject(entity);
			switched = true;
		}
		else if (ImGui::Button("Verlet")) {
			delete physicsObject;
			physicsObject = new VerletObject(entity);
			switched = true;
		}
		else if (ImGui::Button("Static")) {
			delete physicsObject;
			physicsObject = new StaticObject(entity);
			switched = true;
		}
		if (switched) {
			ImGui::CloseCurrentPopup();
			physicsObject->setPos({ pos[0], pos[1] });
			physicsObject->setVel({ vel[0], vel[1] });
			physicsObject->setAcc({ acc[0], acc[1] });
		}
		ImGui::EndPopup();
	}

	if (entity->shape->getType() == ShapeType::Plane) {
		ImGui::BeginDisabled();
	}
	if (ImGui::Checkbox("Infinite Mass", &infiniteMass)) {
		if (infiniteMass) {
			physicsObject->invMass = 0;
		}
		else {
			physicsObject->setMass(1.f);
		}
	}

	ImGui::SameLine();
	if (infiniteMass) {
		ImGui::BeginDisabled();
	}
	float newMass = physicsObject->getMass();
	if (ImGui::DragFloat("Mass", &newMass, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
		physicsObject->setMass(newMass);
	}
	if (infiniteMass) {
		ImGui::EndDisabled();
	}
	if (entity->shape->getType() == ShapeType::Plane) {
		ImGui::EndDisabled();
	}


	if (ImGui::DragFloat2("Position##Physics", pos, 0.1f, 1.f)) {
		physicsObject->setPos({ pos[0], pos[1] });
	}

	if (ImGui::DragFloat2("Velocity", vel, 0.1f, 1.f)) {
		physicsObject->setVel({ vel[0], vel[1] });
	}

	if (ImGui::DragFloat2("Acceleration", acc, 0.1f, 1.f)) {
		physicsObject->setAcc({ acc[0], acc[1] });
	}
}
