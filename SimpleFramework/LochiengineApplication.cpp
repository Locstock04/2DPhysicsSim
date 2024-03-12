#include "LochiengineApplication.h"

#include "imgui.h"

#include "DrawHandler.h"

LochiengineApplication::LochiengineApplication()
{
}

LochiengineApplication::~LochiengineApplication()
{
}

void LochiengineApplication::Update(float delta)
{
	// Can't have in the constructor as the lines haven't been created yet
	DrawHandler::SetLineRenderer(lines);
	if (rightMouseDown) {
		lochiengine.MoveAllToward(cursorPos, delta);
	}
	lochiengine.Update(delta);
}

void LochiengineApplication::OnLeftClick()
{
	if (ImGui::GetIO().WantCaptureMouse) {
		return;
	}

	lochiengine.CreateDefaultEntity(cursorPos);
}

void LochiengineApplication::OnRightClick()
{
	if (!ImGui::GetIO().WantCaptureMouse) {
		return;
	}
}
