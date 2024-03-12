#pragma once

class LineRenderer;
struct Circle;
struct Box;
struct Plane;

class DrawHandler
{
	static LineRenderer* lines;
public:
	static void SetLineRenderer(LineRenderer* _lines);

	static void DrawCircle(Circle* circle);
	static void DrawBox(Box* box);
	static void DrawPlane(Plane* plane);
};
