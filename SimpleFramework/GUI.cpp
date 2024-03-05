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

void GUI::Update(LineRenderer* lines)
{
	if (drawCreatingShape && creatingEntity->shape != nullptr) {
		creatingEntity->Draw(lines);
	}
	
	EntityEditorMenu();
	//ForceMenu();


}

//TODO: Make menu to apply forces to all objects
void GUI::ForceMenu()
{
	ImGui::Begin("Forces", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);


	//TODO: Show some sort of text for when there are no entities to edit

	ImGui::SliderInt("Index", &selectionIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
	glm::clamp(selectionIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));

	ImGui::BeginDisabled();
	if (ImGui::CollapsingHeader("Entity")) {

	}
	ImGui::EndDisabled();

	ImGui::End();
}

void GUI::EntityEditorMenu()
{
	//TODO: Keep track of current shape
	ImGui::Begin("Entity Menu", nullptr,
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar// |
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize// |
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
	);


	ImGui::Checkbox("Edit Existing Object", &editMode);
	if (editMode) {
		ImGui::SliderInt("Index", &selectionIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		glm::clamp(selectionIndex, 0, glm::max(0, (int)lochiengine->entities.size() - 1));
		//TODO: Show some sort of text for when there are no entities to edit
		if (lochiengine->entities.size() != 0) {
			EntityGUI(lochiengine->entities[selectionIndex]);
		}
		ImGui::End();
		return;
	}

	EntityGUI(creatingEntity);

	ImGui::Spacing();
	if (ImGui::Button("Create object")) {
		Shape* newShape;
		//TODO: I feel like this switch could be better written
		switch (creatingEntity->shape->getType())
		{
		case ShapeType::Circle:
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
			newShape = new Circle(*(Circle*)creatingEntity);
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

		lochiengine->entities.push_back(new Entity({ shapePos[0], shapePos[1] }, newShape, newPhysicsObject));

	}
	ImGui::End();

}

void GUI::EntityGUI(Entity* entity)
{
	if (ImGui::CollapsingHeader("Entity")) {
		if (ImGui::DragFloat2("Position", shapePos, 0.1f, 1.f)) {
			entity->pos = { shapePos[0], shapePos[1] };
		}
	}

	if (ImGui::CollapsingHeader("Shape")) {
		ImGui::Checkbox("Preview Shape", &drawCreatingShape);

		std::string shapeName;
		switch (entity->shape->getType())
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
				delete entity->shape;
				entity->shape = new Circle(entity, 1);
				ImGui::CloseCurrentPopup();
			}
			else if (ImGui::Button("Box")) {
				delete entity->shape;
				entity->shape = new Box(entity, 1, 1);
				ImGui::CloseCurrentPopup();
			}
			else if (ImGui::Button("Plane")) {
				delete entity->shape;
				entity->shape = new Plane(entity, { 1.f, 0.f }, -1.f);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		float tempWidth;
		float tempHeight;
		float tempAngle;
		if (ImGui::ColorEdit3("Colour", colour)) {
			entity->shape->colour = { colour[0], colour[1], colour[2] };
		}
		switch (entity->shape->getType())
		{
		case ShapeType::Circle:
			ImGui::DragFloat("Radius", &((Circle*)(entity->shape))->radius, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
			break;
		case ShapeType::Box:
			tempWidth = ((Box*)(entity->shape))->getWidth();
			tempHeight = ((Box*)(entity->shape))->getHeight();
			if (ImGui::DragFloat("Width", &tempWidth, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Box*)(entity->shape))->setWidth(tempWidth);
			}
			if (ImGui::DragFloat("Height", &tempHeight, 0.1f, 0.1f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Box*)(entity->shape))->setHeight(tempHeight);
			}
			break;
		case ShapeType::Plane:
			tempAngle = ((Plane*)(entity->shape))->getNormalDegrees();
			ImGui::DragFloat("Displacement", &((Plane*)(entity->shape))->displacement, 0.1f, -FLT_MAX, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
			if (ImGui::DragFloat("Angle", &tempAngle, 0.1f, -FLT_MAX, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
				((Plane*)(entity->shape))->setNormal(tempAngle);
			}


			break;
		default:
			//TODO: what here
			break;
		}

	}

	if (ImGui::CollapsingHeader("Physics")) {
		if (entity->shape->getType() == ShapeType::Plane) {
			ImGui::BeginDisabled();

		}
		if (ImGui::Checkbox("Infinite Mass", &infiniteMass)) {
			if (infiniteMass) {
				entity->physicsObject->invMass = 0;
			}
			else {
				entity->physicsObject->setMass(1.f);
			}
		}
		
		ImGui::SameLine();
		if (infiniteMass) {
			ImGui::BeginDisabled();
		}
		mass = entity->physicsObject->getMass();
		if (ImGui::DragFloat("Mass", &mass, 0.1f, 0.1, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			entity->physicsObject->setMass(mass);
		}
		if (infiniteMass) {
			ImGui::EndDisabled();
		}

		/*float tempInvMass = entity->physicsObject->invMass;
		if (ImGui::DragFloat("Inverse Mass", &tempInvMass, 0.1f, 0.f, FLT_MAX, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)) {
			entity->physicsObject->invMass = tempInvMass;
		}*/
		
		std::string physicsTypeName;
		switch (entity->physicsObject->getType())
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
				delete entity->physicsObject;
				entity->physicsObject = new EulerObject(entity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Verlet")) {
				delete entity->physicsObject;
				entity->physicsObject = new VerletObject(entity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Static")) {
				delete entity->physicsObject;
				entity->physicsObject = new StaticObject(entity);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (entity->shape->getType() == ShapeType::Plane) {
			ImGui::EndDisabled();
		}

	}
}
