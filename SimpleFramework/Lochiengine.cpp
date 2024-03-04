#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Lochiengine::Lochiengine()
{
	entityCreatingGUI = new Entity({ 0.f, 0.f }, new Circle(1), new EulerObject());


	//entities[0]->physicsObject->AddImpulse({ 2, 2 });

	//int lineSides = 0;
	//for (int i = 0; i < lineSides; i++)
	//{
	//	entities.push_back(new Entity({ 0, 0 }, new Plane(float(i * (360 /lineSides)), -10)));
	//}


	entities.push_back(new Entity({ 0, 0 }, new Plane(180, -10)));

}

Lochiengine::~Lochiengine()
{
	delete entityCreatingGUI;
	delete CollisionDatum::emptyTemp;
	while (!entities.empty())
	{
		delete entities.back();
		entities.pop_back();
	}
}

void Lochiengine::Update(float delta)
{
	if (rightMouseDown) {
		for (Entity* entity : entities)
		{
			// "accurate" gravity
			//float gravitionalConstant = 6.674 * glm::pow(10, -11);
			//float massOfCursor = 1000000000000;
			//float distanceFromMouse = glm::distance(entity->pos, cursorPos);
			//if (distanceFromMouse == 0.0f) { continue; }
			//Vec2 fromEntityToCursor = glm::normalize(cursorPos - entity->pos);
			//float acc = (gravitionalConstant * massOfCursor) / (distanceFromMouse * distanceFromMouse);
			//entity->physicsObject->setAcc(acc * fromEntityToCursor);

			entity->physicsObject->setAcc(2.5f * /*glm::normalize*/(cursorPos - entity->pos));
		}
	}
	else {
		for (Entity* entity : entities)
		{
			entity->physicsObject->setAcc({0, 0});
		}
	}

	for (Entity* entity : entities)
	{
		entity->Update(delta);
	}

	for (size_t i = 0; i < physicsIterations; i++)
	{
		CollisionHandling();
	}

	UpdateGUI();
	Draw();
	
}

void Lochiengine::OnLeftClick()
{

}

void Lochiengine::OnRightClick()
{

}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity* entity : entities)
	{
		entity->Draw(lines);
	}

	if (previewGuiShape && entityCreatingGUI->shape != nullptr) {
		entityCreatingGUI->Draw(lines);
	}
}

void Lochiengine::UpdateGUI()
{
	//TODO: Keep track of current shape
	ImGui::Begin("Creator Menu", nullptr,
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar// |
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize// |
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
	);
	if (ImGui::CollapsingHeader("Entity")) {
		if (ImGui::DragFloat2("Position", posGUI, 0.1f, 1.f)) {
			entityCreatingGUI->pos = { posGUI[0], posGUI[1] };
		}
	}

	if (ImGui::CollapsingHeader("Shape")) {
		ImGui::Checkbox("Preview Shape", &previewGuiShape);

		std::string shapeName;
		switch (entityCreatingGUI->shape->getType())
		{
		case ShapeType::Circle:
			shapeName = "Circle";
			break;
		case ShapeType::Box:
			shapeName = "Box";
			break;
		case ShapeType::Plane:
			shapeName = "Plane";
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
				delete entityCreatingGUI->shape;
				entityCreatingGUI->shape = new Circle(entityCreatingGUI, 1);
				ImGui::CloseCurrentPopup();
			}
			else if (ImGui::Button("Box")) { 
				delete entityCreatingGUI->shape;
				entityCreatingGUI->shape = new Box(entityCreatingGUI, 1, 1);
				ImGui::CloseCurrentPopup(); 
			}
			else if (ImGui::Button("Plane")) { 
				delete entityCreatingGUI->shape;
				entityCreatingGUI->shape = new Plane(entityCreatingGUI, {1.f, 0.f}, -1.f);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		float tempWidth;
		float tempHeight;
		float tempAngle;
		if (ImGui::ColorEdit3("Colour", colour)) {
			entityCreatingGUI->shape->colour = { colour[0], colour[1], colour[2] };
		}
		switch (entityCreatingGUI->shape->getType())
		{
		case ShapeType::Circle:
			ImGui::DragFloat("Radius", &((Circle*)(entityCreatingGUI->shape))->radius, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
			break;
		case ShapeType::Box:
			tempWidth = ((Box*)(entityCreatingGUI->shape))->getWidth();
			tempHeight = ((Box*)(entityCreatingGUI->shape))->getHeight();
			if (ImGui::DragFloat("Width", &tempWidth, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Box*)(entityCreatingGUI->shape))->setWidth(tempWidth);
			}
			if (ImGui::DragFloat("Height", &tempHeight, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Box*)(entityCreatingGUI->shape))->setHeight(tempHeight);
			}
			break;
		case ShapeType::Plane:
			tempAngle = ((Plane*)(entityCreatingGUI->shape))->getNormalDegrees();
			ImGui::DragFloat("Displacement", &((Plane*)(entityCreatingGUI->shape))->displacement, 0.1f, 0.f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
			if (ImGui::DragFloat("Angle", &tempAngle, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Plane*)(entityCreatingGUI->shape))->setNormal(tempAngle);
			}
		

			break;
		default:
			//TODO: what here
			break;
		}

	}
	
	if (ImGui::CollapsingHeader("Physics")) {
		if (ImGui::Checkbox("Infinite Mass", &infiniteMassGUI)) {
			if (infiniteMassGUI) {
				entityCreatingGUI->physicsObject->invMass = 0;
			}
			else {
				entityCreatingGUI->physicsObject->setMass(1.f);
			}
		}
		ImGui::SameLine();
		if (infiniteMassGUI) {
			ImGui::BeginDisabled();
		}
		massGUI = entityCreatingGUI->physicsObject->getMass();
		if (ImGui::DragFloat("Mass", &massGUI, 0.1f, 0.1, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			entityCreatingGUI->physicsObject->setMass(massGUI);
		}
		if (infiniteMassGUI) {
			ImGui::EndDisabled();
		}
		
		/*float tempInvMass = entityCreatingGUI->physicsObject->invMass;
		if (ImGui::DragFloat("Inverse Mass", &tempInvMass, 0.1f, 0.f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			entityCreatingGUI->physicsObject->invMass = tempInvMass;
		}*/

		std::string physicsTypeName;
		switch (entityCreatingGUI->physicsObject->getType())
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
			if (ImGui::Button("Euler")) {
				delete entityCreatingGUI->physicsObject;
				entityCreatingGUI->physicsObject = new EulerObject(entityCreatingGUI);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Verlet")) {
				delete entityCreatingGUI->physicsObject;
				entityCreatingGUI->physicsObject = new VerletObject(entityCreatingGUI);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Static")) {
				delete entityCreatingGUI->physicsObject;
				entityCreatingGUI->physicsObject = new StaticObject(entityCreatingGUI);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

	}

	//TODO: Rather then creating a new object and copying stuff over, the current GUI object could be moved to become the actual object and a new object be created for the menu?
	ImGui::Spacing();
	if (ImGui::Button("Create object")) {
		Shape* newShape;
		//TODO: I feel like this switch could be better written
		switch (entityCreatingGUI->shape->getType())
		{
		case ShapeType::Circle:
			newShape = new Circle(*(Circle*)entityCreatingGUI->shape);
			break;
		case ShapeType::Box:
			newShape = new Box(*(Box*)entityCreatingGUI->shape);
			break;
		case ShapeType::Plane:
			newShape = new Plane(*(Plane*)entityCreatingGUI->shape);
			break;
		default:
			//TODO: What here
			newShape = new Circle(*(Circle*)entityCreatingGUI);
			break;
		}

		PhysicsObject* newPhysicsObject;
		switch (entityCreatingGUI->physicsObject->getType())
		{
		case PhysicsObjectType::Euler:
			newPhysicsObject = new EulerObject(*(EulerObject*)entityCreatingGUI->physicsObject);
			break;
		case PhysicsObjectType::Verlet:
			newPhysicsObject = new VerletObject(*(VerletObject*)entityCreatingGUI->physicsObject);
			break;
		case PhysicsObjectType::Static:
			newPhysicsObject = new StaticObject(*(StaticObject*)entityCreatingGUI->physicsObject);
			break;
		default:
			newPhysicsObject = new EulerObject(*(EulerObject*)entityCreatingGUI->physicsObject);

			break;
		}

		entities.push_back(new Entity({ posGUI[0], posGUI[1] }, newShape, newPhysicsObject));



	}
	ImGui::End();


	ImGui::Begin("Another Window!", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);


	ImGui::SliderInt("Index", &selectionIndex, 0, entities.size());
	glm::clamp(selectionIndex, 0, (int)entities.size());

	ImGui::BeginDisabled();
	if (ImGui::CollapsingHeader("Entity")) {

	}
	ImGui::EndDisabled();

	ImGui::End();



}



void Lochiengine::CollisionHandling()
{
	// Collision Detection

	std::vector<CollisionDatum> collisions;

	for (int i = 0; i < entities.size(); i++)
	{
		for (int j = i + 1; j < entities.size(); j++)
		{
			if (entities[i]->physicsObject->isStatic() && entities[j]->physicsObject->isStatic()) { continue; }
			// Remove potential non touching circles 


			// Bounding boxes
			//if (rightMouseDown) {
			/*if (!(glm::abs(entities[i].pos.x - entities[j].pos.x) < entities[i].radius + entities[j].radius)) {
				continue;
			}
			else {
				if (!(glm::abs(entities[i].pos.y - entities[j].pos.y) < entities[i].radius + entities[j].radius)) {
					continue;
				}
			}*/
			//}

			CollisionDatum collisionDatum = GetCollision(entities[i], entities[j]);
			if (collisionDatum.overlap < 0) {
				continue;
			}
			collisions.push_back(collisionDatum);
		}
	}

	// Collision Response

	for (auto i = collisions.begin(); i != collisions.end(); i++)
	{
		i->Solve();
	}
}

