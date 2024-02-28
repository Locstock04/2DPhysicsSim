#pragma once

#include "LineRenderer.h"

#include "Maths.h"

class Entity;
class LineRender;


enum class ShapeType {
	Circle,
	Box,
	Plane,
};

struct Shape {
	Entity* parent;
	Shape(Entity* _parent);
	Shape();
	virtual void Draw(LineRenderer* lines) = 0;
	virtual ShapeType getType() const = 0;
	glm::vec3 colour = { 1.f, 1.f, 1.f };
};

struct Circle : Shape {
	float radius;
	Circle(float r);
	Circle(Entity* _parent, float r);
	virtual void Draw(LineRenderer* lines) override;
	virtual ShapeType getType() const override { return ShapeType::Circle; }
};

struct Box : Shape {
private:

	float width;
	float height;

	float halfWidth;
	float halfHeight;

	float diagonal;
	float halfDiagonal;

public:
	void setWidth(float _width);
	void setHeight(float _height);
	float getWidth() const;
	float getHeight() const;

	float getHalfWidth() const;
	float getHalfHeight() const;
	
	void CalculateDiagonal();
	float getDiagonal() const;
	float getHalfDiagonal() const;

	//TODO: should these functions exist
	float getTop() const;
	float getBottom() const;
	float getLeft() const;
	float getRight() const;
	


	Box(float _width, float _height);
	Box(Entity* _parent, float _width, float _height);

	
	virtual void Draw(LineRenderer* lines) override;


	virtual ShapeType getType() const override { return ShapeType::Box; }

private:
	//Vec2 getTopLeft() const;
	//Vec2 getTopRight() const;
	//Vec2 getBottomLeft() const;
	//Vec2 getBottomRight() const;

};


struct GlobalShape : Shape {
	GlobalShape();
	GlobalShape(Entity* _parent);
};

struct Plane : GlobalShape {
	Vec2 normal;
	float displacement;

	Plane(Vec2 _normal, float _displacement);
	Plane(float angle, float _displacement);
	Plane(Entity* _parent, Vec2 _normal, float _displacement);
	virtual void Draw(LineRenderer* lines) override;

	virtual ShapeType getType() const override { return ShapeType::Plane; }

	Vec2 getTangent() const { return { normal.y, -normal.x }; };

	void setNormal(float degrees);
	void setNormal(Vec2 _normal);
	float getNormalDegrees() const;
};
