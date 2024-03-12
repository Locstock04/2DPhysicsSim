#include "DrawHandler.h"

#include "LineRenderer.h"
#include "Entity.h"

LineRenderer* DrawHandler::lines = nullptr;

void DrawHandler::SetLineRenderer(LineRenderer* _lines)
{
	lines = _lines;
}

void DrawHandler::DrawCircle(Circle* circle)
{
	lines->DrawCircle(circle->parent->pos, circle->radius, circle->colour);
	lines->DrawCross(circle->parent->pos, circle->radius / sqrtf(2), circle->colour);
}

void DrawHandler::DrawBox(Box* box)
{
	Vec2 topLeft(box->getLeft(), box->getTop());
	Vec2 topRight(box->getRight(), box->getTop());
	Vec2 bottomLeft(box->getLeft(), box->getBottom());
	Vec2 bottomRight(box->getRight(), box->getBottom());

	lines->SetColour(box->colour);
	lines->AddPointToLine(topLeft);
	lines->AddPointToLine(topRight);
	lines->AddPointToLine(bottomRight);
	lines->AddPointToLine(bottomLeft);
	lines->FinishLineLoop();

	lines->DrawLineSegment(topLeft, bottomRight);
	lines->DrawLineSegment(topRight, bottomLeft);
}

void DrawHandler::DrawPlane(Plane* plane)
{
	Vec2 tangent(plane->normal.y, -plane->normal.x);


	lines->DrawLineSegment(plane->normal * plane->displacement - 2.f * plane->normal, plane->normal * plane->displacement, plane->colour);
	lines->DrawLineSegment(plane->normal * plane->displacement - plane->normal + plane->getTangent(), plane->normal * plane->displacement, plane->colour);
	lines->DrawLineSegment(plane->normal * plane->displacement - plane->normal - plane->getTangent(), plane->normal * plane->displacement, plane->colour);

	lines->DrawLineSegment(plane->normal * plane->displacement + tangent * 2048.0f, plane->normal * plane->displacement - tangent * 2048.0f, plane->colour);

}
