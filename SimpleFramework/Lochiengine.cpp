#include <iostream>

#include "Lochiengine.h"
#include "CollisionFunctions.h"

#include <sstream>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Lochiengine::Lochiengine()
{


	//entities.push_back(new Entity({ 0, 0 }, new Circle(0.5f)));
	//delete entities[0]->physicsObject;
	//entities[0]->physicsObject = new VerletObject(entities[0]);
	//entities[0]->physicsObject->invMass = 0.0f;

	//entities.push_back(new Entity({ 0, 0 }, new Box(2, 6)));
	//entities.push_back(new Entity({ 3, 3 }, ShapeType::Box));

	//entities[0]->physicsObject->AddImpulse({ 2, 2 });

	//int lineSides = 0;
	//for (int i = 0; i < lineSides; i++)
	//{
	//	entities.push_back(new Entity({ 0, 0 }, new Plane(float(i * (360 /lineSides)), -10)));
	//}

	//
	//entities.push_back(new Entity({ 0, 0 }, new Circle(3)));
	//entities.push_back(new Entity({ 0, 0 }, new Box(1, 1)));
	////entities[0]->physicsObject->invMass = 0;

	entities.push_back(new Entity({ 0, 0 }, new Plane(180, -10)));

}

Lochiengine::~Lochiengine()
{
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
			if (entities[0] == entity) {
				//continue;
			}


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

	//entities[0].position = cursorPos;
	//delta /= physicsIterations;

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
	//entities.push_back(new Entity(cursorPos, ShapeType::Circle));
	//entities.push_back(new Entity(cursorPos, ShapeType::Box));

}

void Lochiengine::OnRightClick()
{
	//entities[0]->physicsObject->AddImpulse(-cursorPos + entities[0]->pos);

}

void Lochiengine::Draw()
{
	lines->SetColour(Vec3(0, 1, 1));

	for (Entity* entity : entities)
	{
		entity->Draw(lines);
	}



	
}



void Lochiengine::UpdateGUI()
{
	bool my_tool_active = true;
	ImGui::Begin("Shape Creator Menu", &my_tool_active,
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar// |
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize// |
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
	);

	std::string shape;
	switch (currentShape)
	{
	case ShapeType::Circle:
		shape = "Shape: Circle";
		break;
	case ShapeType::Box:
		shape = "Shape: Box";
		break;
	case ShapeType::Plane:
		shape = "Shape: Plane";
		break;
	default:
		break;
	}
	
	if (ImGui::Button(shape.c_str())) {
		ImGui::OpenPopup("Shape Type");
	}

	if (ImGui::IsPopupOpen("Shape Type")) {
		ImGui::BeginPopup("Shape Type");
		if (ImGui::Button("Circle")) { 
			currentShape = ShapeType::Circle;
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Box")) { 
			currentShape = ShapeType::Box;
			ImGui::CloseCurrentPopup(); 
		}
		if (ImGui::Button("Plane")) { 
			currentShape = ShapeType::Plane;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	float tempWidth = boxGUI.getWidth();
	float tempHeight = boxGUI.getHeight();
	float tempAngle = planeGUI.getNormalDegrees();
	switch (currentShape)
	{
	case ShapeType::Circle:
		ImGui::DragFloat2("Position", posGUI);
		ImGui::DragFloat("Radius", &circleGUI.radius, 0.1f, 1.f);
		break;
	case ShapeType::Box:
		ImGui::DragFloat2("Position", posGUI);
		if (ImGui::DragFloat("Width", &tempWidth, 0.1f, 1.f)) {
			boxGUI.setWidth(tempWidth);
		}
		if (ImGui::DragFloat("Height", &tempHeight, 0.1f, 1.f)) {
			boxGUI.setHeight(tempHeight);
		}
		break;
	case ShapeType::Plane:
		
		ImGui::DragFloat("Displacement", &planeGUI.displacement, 0.1f, 1.f);
		if (ImGui::DragFloat("Angle", &tempAngle, 0.1f, 1.f)) {
			planeGUI.setNormal(tempAngle);
		}
		

		break;
	default:
		//TODO: what here
		break;
	}

	ImGui::Spacing();
	if (ImGui::Button("Create object")) {
		Shape* newShape;
		switch (currentShape)
		{
		case ShapeType::Circle:
			newShape = new Circle(circleGUI);
			break;
		case ShapeType::Box:
			newShape = new Box(boxGUI);
			break;
		case ShapeType::Plane:
			newShape = new Plane(planeGUI);
			break;
		default:
			//TODO: What here
			newShape = new Circle(circleGUI);
			break;
		}

		entities.push_back(new Entity({ posGUI[0], posGUI[1] }, newShape));
	}

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

